#ifndef _NEURALNETWORKLAYER_H_
#define _NEURALNETWORKLAYER_H_

class NeuralNetworkLayer { 
public: 
     int               totalNeurons; //numero de neuronios da camada
     int               totalNextNeurons;  //numero de neuronios da camada inferior
     int               totalPrevNeurons; //numero de neuronios da camada superior
     
     double**          weights; 
     double**          weightChanges; 
     
     double*           neuronValues; 
     double*           desiredValues; 
     
     double*           errors; 
     
     double*           biasWeights; 
     double*           biasValues; 
     
     double            learningRate; 
     bool              useLinearOutput; 
     bool              useMomentum; 
     double            momentumFactor; 
     
     NeuralNetworkLayer*     prevLayer; 
     NeuralNetworkLayer*     nextLayer; 
     NeuralNetworkLayer(); 
     
     void     initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child); 
     void     shutdown(void); 
     void     randomizeWeights(void); 
     void     calculateErrors(void); 
     void     adjustWeights(void); 
     void     calculateNeuronValues(void); 
};

#endif //_NEURALNETWORKLAYER_H_
