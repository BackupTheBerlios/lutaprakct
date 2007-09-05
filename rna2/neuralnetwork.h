#ifndef _NEURALNETWORK_H_
#define _NEURALNETWORK_H_

#include "neuralnetworklayer.h"
#include "stdarg.h"
#include <vector>

class neuralNetwork{
	
public:
	
	NeuralNetworkLayer *layers;
	
	//duas formas de inicializar, a primeira passa a quantidade de neuronios em cada camada 
	//a segunda passa o arquivo com topologia e conjunto de treinamento
	void initialize(int numLayers, char* format, ...);
	bool initialize(char* filename);
	
	void learn(char* filename, char* errorLearnFile = 0);
	void learn( std::vector<float>* input, std::vector<float>* output, char* errorFile = 0);
	
	//envia um conjunto de dados de uma vez
	void setInput( std::vector<float>* input, char* errorFile = 0 );
	void setInput( char* inputFile, char* errorFile = 0 );
	
	void shutdown();
	
	void setInput(int i, double value);
	double getOutput(int i);
	
	void setDesiredOutput(int i, double value);
	
	void feedForward();
	void backPropagate();
	
	int getMaxOutputID();
	
	double calculateError();
	
	void setLearningRate(double rate);
	void setLinearOutput(bool lo);
	void setMomentum(bool um, double valor);
	
	void printStatus(char *filename);
	
	float getMinError(){return minError;};
	int getMaxEpoch(){return maxEpoch;};
	
	void setMinError(float a){ minError = a;};
	void setMaxEpoch(int a){ maxEpoch = a;};
	
private:

	int numLayers;
	
	int maxEpoch;
	float minError;
};


#endif //_NEURALNETWORK_H_
