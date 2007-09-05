#include "neuralnetworklayer.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

NeuralNetworkLayer::NeuralNetworkLayer() { 
     prevLayer = NULL; 
     nextLayer = NULL; 
     useLinearOutput = false; 
     useMomentum = false; 
     momentumFactor = 0.9; 
} 

void NeuralNetworkLayer::initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child) { 

     // Aloca memoria
     neuronValues = (double*) malloc(sizeof(double) * totalNeurons); 
     desiredValues = (double*) malloc(sizeof(double) *   totalNeurons); 
     errors = (double*) malloc(sizeof(double) * totalNeurons); 
     
     if(parent) 
     	prevLayer = parent; 
     	
     if(child) { //se tem uma proxima camada, entao aloca os pesos
          nextLayer = child; 
          weights = (double**) malloc(sizeof(double*) *  totalNeurons); 
          weightChanges = (double**) malloc(sizeof(double*) * totalNeurons); 
          
          for(int i = 0; i<totalNeurons; i++) { 
               weights[i] = (double*) malloc(sizeof(double) * totalNextNeurons); 
               weightChanges[i] = (double*) malloc(sizeof(double) * totalNextNeurons); 
          } 
          
          biasValues = (double*) malloc(sizeof(double) * totalNextNeurons); 
          biasWeights = (double*) malloc(sizeof(double) * totalNextNeurons); 
          
     } else {  //se nao tem proxima camada entao eh saida. sem pesos e bias
          weights = NULL; 
          biasValues = NULL; 
          biasWeights = NULL; 
          weightChanges = NULL; 
     } 
     
     // zera tudo
     for(int i=0; i<totalNeurons; i++) { 
          neuronValues[i] = 0; 
          desiredValues[i] = 0; 
          errors[i] = 0; 
          if(nextLayer) //se nao eh camada de saida, temm q zerar os pesos tbm
               for(int j=0; j<totalNextNeurons; j++) { 
                    weights[i][j] = 0; 
                    weightChanges[i][j] = 0; 
               } 
     } 
     
     // inicializa o bias (com -1) e os biasWeight com 0
     if(nextLayer) {
          for(int j=0; j<totalNextNeurons; j++){ 
               biasValues[j] = -1; 
               biasWeights[j] = 0; 
          } 
     }
} 

/*
 * deleta o espaço alocado
 */
void NeuralNetworkLayer::shutdown(void) { 

     free(neuronValues); 
     free(desiredValues); 
     free(errors); 
     if(weights) { 
          for(int i = 0; i<totalNeurons; i++) { 
               free(weights[i]); 
               free(weightChanges[i]); 
          } 
          free(weights); 
          free(weightChanges); 
     } 
     if(biasValues) free(biasValues); 
     if(biasWeights) free(biasWeights); 
} 

/*
 * escolhe um valor entre -1 e 1 para cada peso. o mesmo para os biasweight
 * chamado apenas 1 vez no inicio do treinamento.
 */
void NeuralNetworkLayer::randomizeWeights(void) { 
     int     min = 0; 
     int     max = 200; 
     int     number; 
     srand( (unsigned)time( NULL ) ); 
     
     for(int i=0; i<totalNeurons; i++) { 
          for(int j=0; j<totalNextNeurons; j++) { 
               number = (((abs(rand())%(max-min+1))+min)); 
               if(number>max) 
                    number = max; 
               if(number<min) 
                   number = min; 
               weights[i][j] = number / 100.0f - 1; 
          } 
     } 
     
     for(int j=0; j<totalNextNeurons; j++) { 
               number = (((abs(rand())%(max-min+1))+min)); 
               if(number>max) 
                    number = max; 
               if(number<min) 
                    number = min; 
               biasWeights[j] = number / 100.0f - 1; 
     } 
} 

/* calcula o input de cada neuronio e depois usa a funçao de ativaçao para calcular
 * o valor final
 */

void NeuralNetworkLayer::calculateNeuronValues(void) { 

     double x; 
     if(prevLayer) { 
          for(int j=0; j<totalNeurons; j++) { 
               x = 0; 
               for(int i=0; i<totalPrevNeurons; i++) { 
                    x += prevLayer->neuronValues[i] * prevLayer->weights[i][j]; 
               }
               x += prevLayer->biasValues[j] * prevLayer->biasWeights[j]; 
               
               if((nextLayer == NULL) && useLinearOutput) 
                    neuronValues[j] = x; 
               else //aplica sigmoide se nao for linear
                    neuronValues[j] = 1.0f/(1+exp(-x)); 
          } 
     } 
}



void NeuralNetworkLayer::calculateErrors(void) { 

     double sum; 
     if(nextLayer == NULL){ //se for a camada de saida
          for(int i=0; i<totalNeurons; i++) 
                 errors[i] = (desiredValues[i] - neuronValues[i]) * neuronValues[i] *  (1.0f - neuronValues[i]);  
     } else if(prevLayer == NULL) { // se for a camada de entrada 
          for(int i=0; i<totalNeurons; i++)  
               errors[i] = 0.0f; 
     } else { //se for uma camada interna 
          for(int i=0; i<totalNeurons; i++) { 
               sum = 0; 
               for(int j=0; j<totalNextNeurons; j++) {
                    sum += nextLayer->errors[j] * weights[i][j]; 
               }
               
               errors[i] = sum * neuronValues[i] * (1.0f - neuronValues[i]); 
          } 
     } 
} 

void NeuralNetworkLayer::adjustWeights(void) { 
	
     double dw; 
     if(nextLayer) { 
          for(int i=0; i<totalNeurons; i++) { 
               for(int j=0; j<totalNextNeurons; j++) { 
                    dw = learningRate * nextLayer->errors[j] * 
                          neuronValues[i]; 
                    if(useMomentum){ 
                         weights[i][j] += dw + momentumFactor * weightChanges[i][j]; 
                         weightChanges[i][j] = dw; 
                    } else { 
                             weights[i][j] += dw; 
                    } 
               } 
          } 
          for(int j=0; j<totalNextNeurons; j++)  
               biasWeights[j] += learningRate * nextLayer->errors[j] * biasValues[j]; 
           
     } 
} 



