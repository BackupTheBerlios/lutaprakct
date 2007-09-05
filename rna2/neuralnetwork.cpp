#include "neuralnetwork.h"

#include <stdlib.h>
#include <math.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include "misc/StringTokenizer.h"

bool neuralNetwork::initialize(char* filename){
	
	std::ifstream file; 
	file.open(filename );
	if (!file){
		std::cout << "File: " << filename << " not found." << std::endl;
		return false;
	}
	
	std::string line;
	int linecount = 0;
	std::vector<float> inputData;
	std::vector<float> outputData;
	int neuronsFirst;
	int neuronsLast;
	std::vector<int> arguments;
	float learningRate;
	
	while (!file.eof()){
		linecount++;
		getline(file, line);
		StringTokenizer tokenizer(line, " ");
		std::string token;
		if (linecount == 1){ //le a primeira linha que contem a topologia
			numLayers = tokenizer.countTokens();
			if (numLayers < 3)
				return false;
			
			std::string token;
			while( tokenizer.hasMoreTokens()) {
				tokenizer.nextToken(token);
				arguments.push_back(atoi(token.c_str()));
			}
				
			layers = new NeuralNetworkLayer[numLayers];
			int j = numLayers;
			int i = 0;
			 
			while(j > 0){
			 	
				layers[i].totalNeurons = arguments[i];
				
				if (i != (numLayers -1))
					layers[i].totalNextNeurons = arguments[i+1];
				else //se for o ultimo layer
					layers[i].totalNextNeurons = 0;
					
				if (i != 0) //se nao for o primeiro layer
					layers[i].totalPrevNeurons = arguments[i-1];
				else
					layers[i].totalPrevNeurons = 0;
				
				if ( i == 0 )
					layers[i].initialize(arguments[i], NULL, &layers[i+1]);
				else if ( i == (numLayers-1) )
					layers[i].initialize(arguments[i], &layers[i-1], NULL);
				else //se so tiverem 3 camadas
					 layers[i].initialize(arguments[i], &layers[i-1], &layers[i+1]);
							
				layers[i].randomizeWeights();
				i++;
				j--;	
			} 
			neuronsFirst = arguments[0];
			neuronsLast = arguments[numLayers-1];	
		}else if (linecount == 2){ //le segunda linha
			sscanf(line.c_str(), "%f %d %f", &minError, &maxEpoch, &learningRate );
			setLearningRate(learningRate);
			setMomentum(true, 0.9);
		}else{
			int tokenCount = 0; 
			while( tokenizer.hasMoreTokens()) {
				tokenCount++;
				tokenizer.nextToken(token);
				if (tokenCount <= neuronsFirst ){
					inputData.push_back(atof(token.c_str()));
				}
				else{
					outputData.push_back(atof(token.c_str()));
				}
			}			
		}
	}
		
	file.close(); //nao precisa mais, leu tudo
	return true;
	
}

void neuralNetwork::setInput(char* filename, char* error){
	
	std::ifstream file; 
	file.open(filename );
	if (!file){
		std::cout << "File: " << filename << " not found." << std::endl;
		return;
	}

	std::fstream erroOut;
	if (error)
		erroOut.open(error, std::ios::out);

	std::vector<float> inputData;
	std::vector<float> outputData;
	unsigned int neuronsFirst = layers[0].totalNeurons;
	unsigned int neuronsLast = layers[numLayers-1].totalNeurons;
	std::string line;
	
	while (!file.eof()){
		getline(file, line);
		StringTokenizer tokenizer(line, " ");
		std::string token;
		
		int tokenCount = 0; 
		while( tokenizer.hasMoreTokens()) {
			tokenCount++;
			tokenizer.nextToken(token);
			if (tokenCount <= neuronsFirst ){
				inputData.push_back(atof(token.c_str()));
			}
			else{
				outputData.push_back(atof(token.c_str()));
			}
		}			
	}

	for ( unsigned int k = 0; k < inputData.size()/neuronsFirst; k++){
		for (unsigned int m = 0; m < neuronsFirst; m++){
			setInput(m, inputData.at(k*neuronsFirst + m) );
		}
		feedForward();
		if (error){
			for (unsigned int n = 0; n < neuronsLast; n++){
				erroOut <<  outputData.at(k*neuronsLast + n) << " ";
			}
			for (unsigned int n = 0; n < neuronsLast; n++){
				erroOut << getOutput(n) << " ";
			}
			erroOut << "" << std::endl;
		}
	}
	
}

void neuralNetwork::setInput( std::vector<float>* input, char* outFile ){

	unsigned int neuronsFirst = layers[0].totalNeurons;
	unsigned int neuronsLast = layers[numLayers-1].totalNeurons;

	std::fstream file;
	file.open(outFile, std::ios::out);
	
	for ( unsigned int k = 0; k < input->size()/neuronsFirst; k++){
		for (unsigned int m = 0; m < neuronsFirst; m++){
			setInput(m, input->at(k*neuronsFirst + m) );
		}
		feedForward();
		for (unsigned int n = 0; n < neuronsLast; n++){
			file << getOutput(n) << std::endl;
		}
	}
	
}

void neuralNetwork::learn(char* filename, char* errorLearnFile){
	
	std::ifstream file; 
	file.open(filename );
	if (!file){
		std::cout << "File: " << filename << " not found." << std::endl;
		return;
	}	

	std::fstream erroOut;
	if (errorLearnFile)	
		erroOut.open(errorLearnFile, std::ios::out);
	
	std::vector<float> inputData;
	std::vector<float> outputData;
	std::string line;
	
	while (!file.eof()){
		getline(file, line);
		if (line.length() > 0){
			StringTokenizer tokenizer(line, " ");
			std::string token;
			
			int tokenCount = 0; 
			while( tokenizer.hasMoreTokens()) {
				tokenCount++;
				tokenizer.nextToken(token);
				if (tokenCount <= layers[0].totalNeurons  ){
					inputData.push_back(atof(token.c_str()));
				}
				else{
					outputData.push_back(atof(token.c_str()));
				}
			}			
		}
	} 
	
	float errorTrain = 1.0;
	int c = 0;
	while ( (errorTrain > minError) && (c < maxEpoch) ){
		errorTrain = 0;
		for ( unsigned int k = 0; k < outputData.size()/layers[numLayers-1].totalNeurons; k++){
			//erroOut << "linha: " << k << " ";
			for ( int m = 0; m < layers[0].totalNeurons; m++){
				//erroOut << "i " << m << " " << inputData.at(k*layers[0].totalNeurons + m) << " ";
				setInput(m, inputData.at(k*layers[0].totalNeurons + m) );
			}
			for ( int n = 0; n < layers[numLayers-1].totalNeurons; n++){
				//erroOut << "o " << n  << " " << outputData.at(k*layers[numLayers-1].totalNeurons + n) << " ";
				setDesiredOutput(n, outputData.at(k*layers[numLayers-1].totalNeurons + n));
			}
			feedForward();
			errorTrain += calculateError();
			backPropagate();
			//erroOut << "" << std::endl;
		}
		errorTrain /= 2;
		erroOut << c << " " << errorTrain << std::endl;
		c++;
	}

	return;
	
}

void neuralNetwork::learn(std::vector<float>* inputData, std::vector<float>* outputData, char* errorFile){

	unsigned int neuronsFirst = layers[0].totalNeurons;
	unsigned int neuronsLast = layers[numLayers-1].totalNeurons;

	float errorTrain = 1.0000;
	int c = 0;
	std::fstream erroOut;
	if (errorFile)	
		erroOut.open(errorFile, std::ios::out);
	while ( (errorTrain > minError) && (c < maxEpoch) ){
		errorTrain = 0;
		c++;
		for ( unsigned int k = 0; k < outputData->size()/neuronsLast; k++){
			for (unsigned int m = 0; m < neuronsFirst; m++){
				setInput(m, inputData->at(k*neuronsFirst + m) );
			}
			for (unsigned int n = 0; n < neuronsLast; n++){
				setDesiredOutput(n, outputData->at(k*neuronsLast + n));
			}
		}
		feedForward();
		errorTrain += calculateError();
		backPropagate();
		errorTrain /= 2;
		if (errorFile)
			erroOut << c << " " << errorTrain << std::endl;
	}
	
}

void neuralNetwork::initialize(int x, char* format, ...){
	
	if (x < 3)
		return;
	
	numLayers = x;
	
	std::vector<int> arguments;
	va_list arglist;
	int argument;
	
	va_start(arglist, format);
		while (x--){
			argument = va_arg(arglist, int );
			arguments.push_back(argument);
		}
	va_end(arglist);
	
	layers = new NeuralNetworkLayer[numLayers];
	int j = numLayers;
	int i = 0;
	
	while (j > 0){
		layers[i].totalNeurons = arguments[i];
		
		if (i != (numLayers -1))
			layers[i].totalNextNeurons = arguments[i+1];
		else //se for o ultimo layer
			layers[i].totalNextNeurons = 0;
			
		if (i != 0) //se nao for o primeiro layer
			layers[i].totalPrevNeurons = arguments[i-1];
		else
			layers[i].totalPrevNeurons = 0;
		
		if ( i == 0 )
			layers[i].initialize(arguments[i], NULL, &layers[i+1]);
		else if ( i == (numLayers-1) )
			layers[i].initialize(arguments[i], &layers[i-1], NULL);
		else //se so tiverem 3 camadas
			 layers[i].initialize(arguments[i], &layers[i-1], &layers[i+1]);
					
		layers[i].randomizeWeights();
		i++;
		j--;
	}
	
}

void neuralNetwork::shutdown(){
	int k = 0;
	while (k < numLayers){
		layers[k].shutdown();
		k++;
	}
}

void neuralNetwork::setInput(int i, double value){
	
	if ( (i >= 0) && (i < layers[0].totalNeurons) )
		layers[0].neuronValues[i] = value;
	
}

double neuralNetwork::getOutput(int i){
	
	if ( (i >= 0) && (i < layers[numLayers-1].totalNeurons) )
		return layers[numLayers-1].neuronValues[i];
	return -1000;
	
}

void neuralNetwork::setDesiredOutput(int i, double value){

	if ( (i >= 0) && ( i< layers[numLayers-1].totalNeurons) )
		layers[numLayers-1].desiredValues[i] = value;
	
}

void neuralNetwork::feedForward(){
	int k = 0;
	while (k < numLayers){
		layers[k].calculateNeuronValues();
		k++;
	}
}

void neuralNetwork::backPropagate(){
	//calcula os erros de tras pra frente
	int k = numLayers-1;
	//menos no layer 0 que e a camada de entrada
	while (k != 0){
		layers[k].calculateErrors();
		k--;
	}
	
	//ajusta os pesos de tras pra frente menos na ultima camada
	k = numLayers-2;
	while (k >= 0){
		layers[k].adjustWeights();
		k--;
	}
}

int neuralNetwork::getMaxOutputID(){

	double maxval;
	maxval = layers[numLayers-1].neuronValues[0];
	int id = 0;
	for (int i =1; i < layers[numLayers-1].totalNeurons; i++){
		if (layers[numLayers-1].neuronValues[i] > maxval){
			maxval = layers[numLayers-1].neuronValues[i];
			id = i;
		}
	}
	return id;
}

double neuralNetwork::calculateError(){
	
	double error = 0;
	for (int i = 0; i < layers[numLayers-1].totalNeurons; i++) //camada de saida
		error += pow(layers[numLayers-1].neuronValues[i] - layers[numLayers-1].desiredValues[i], 2 );
	error = error / layers[numLayers-1].totalNeurons;
	return error;
	
}

void neuralNetwork::setLearningRate(double rate){
	int k = 0;
	while (k < numLayers){
		layers[k].learningRate = rate;
		k++;
	}
}

void neuralNetwork::setLinearOutput(bool uselinear){
	
	int k = 0;
	while (k < numLayers){
		layers[k].useLinearOutput = uselinear;
		k++;
	}
	
}

void neuralNetwork::setMomentum(bool usemomentum, double x){
	
	int k = 0;
	while (k < numLayers){
		layers[k].useMomentum = usemomentum;
		layers[k].momentumFactor = x;
		k++;
	}
	
}

void neuralNetwork::printStatus(char* filename){

	FILE *f;
	f = fopen(filename, "w");
	fprintf(f, "----------------------------------\n");
	fprintf(f, "Camada de Entrada\n");	
	fprintf(f, "----------------------------------\n");	
	fprintf(f, "\n");	
	fprintf(f, "Valor dos neuronios: \n");
	fprintf(f, "\n");	
	for (int i = 0; i <layers[0].totalNeurons; i++)
		fprintf(f, "%d = %f\n", i, layers[0].neuronValues[i]);
	fprintf(f, "\n");	
	fprintf(f, "Pesos: \n");		
	fprintf(f, "\n");	
	for (int i = 0; i < layers[0].totalNeurons; i++)
		for (int j = 0; j < layers[0].totalNextNeurons; j++)
			fprintf(f, "W[%d,%d] = %f\n", i, j, layers[0].weights[i][j]);
	fprintf(f, "\n");	
	fprintf(f, "Bias: \n");		
	fprintf(f, "\n");
	for(int i = 0; i < layers[0].totalNextNeurons; i++)
		fprintf(f, "%d = %f\n", i, layers[0].biasWeights[i]);
	fprintf(f, "\n");
	fprintf(f, "\n");		
	fprintf(f, "----------------------------------\n");
	fprintf(f, "Camada de Intermediaria\n");	
	fprintf(f, "----------------------------------\n");	
	fprintf(f, "\n");
	fprintf(f, "Pesos: \n");		
	fprintf(f, "\n");	
	for (int i = 0; i < layers[1].totalNeurons; i++)
		for (int j = 0; j < layers[1].totalNextNeurons; j++)
			fprintf(f, "W[%d,%d] = %f\n", i, j, layers[1].weights[i][j]);
	fprintf(f, "\n");	
	fprintf(f, "Bias: \n");		
	fprintf(f, "\n");
	for(int i = 0; i < layers[1].totalNextNeurons; i++)
		fprintf(f, "%d = %f\n", i, layers[1].biasWeights[i]);	
	fprintf(f, "\n");
	fprintf(f, "\n");	
	fprintf(f, "----------------------------------\n");
	fprintf(f, "Camada de Saida\n");	
	fprintf(f, "----------------------------------\n");		
	fprintf(f, "\n");	
	fprintf(f, "Valor dos neuronios: \n");
	fprintf(f, "\n");	
	for (int i = 0; i <layers[2].totalNeurons; i++)
		fprintf(f, "%d = %f\n", i, layers[2].neuronValues[i]);
	fprintf(f, "\n");	
	fclose(f);
}
