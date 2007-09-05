
#include "somNetwork.h"
#include <cmath>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

bool SomNetwork::initialize(int sizex, int sizey, int iterations, int inputVectorSize ){

	this->sizex = sizex;
	this->sizey = sizey;
	
	numIterations = iterations;
	numFirstNeurons = inputVectorSize;
  
	for (int row = 0; row < sizex; row++)
		for (int col = 0; col < sizey; col++){
			SomNeuron neuron(inputVectorSize);
			neuron.setX(row); neuron.setY(col);
			neurons.push_back(neuron);   //num weights
		}


	radius = sizex > sizey ? sizex/2 : sizey/2;

	timeConstant = numIterations / log(radius);
  
	return true;
}

bool SomNetwork::train(const std::vector<std::vector<double> > &data){

  if (data[0].size() != numFirstNeurons) return false;

  if (done) return true;
 
  while (iterationCount < numIterations){ 
  if (numIterations > 0){
  	
    //escolhe um vetor do teinamento
    int v = rand()%data.size();

    //verifica qual foi o vencedor
    winning = findWinning(data[v]);

    //calcula o raio da vizinhanca
    neighbourhoodRadius = radius * exp(-(double)iterationCount/timeConstant);

	//ajusta os pesos da vizinhanca e do vencedor
    for (int n=0; n < neurons.size(); n++){

      double DistToNodeSq = (winning->getX()-neurons[n].getX()) *
                            (winning->getX()-neurons[n].getX()) +
                            (winning->getY()-neurons[n].getY()) *
                            (winning->getY()-neurons[n].getY()) ;

      double WidthSq = neighbourhoodRadius * neighbourhoodRadius;

      //se ta na vizinhanca
      if (DistToNodeSq < (neighbourhoodRadius * neighbourhoodRadius)){
        influence = exp(-(DistToNodeSq) / (2*WidthSq));
        neurons[n].adjustWeights(data[v], learningRate, influence);
      }

    }

    //reduz o learning rate TODO trocar o 0.1 por um valor  configuravel
    learningRate = 0.1 * exp(-(double)iterationCount/numIterations);
    
    ++iterationCount;

  }else{
    done = true;
  }
  }

  return true;

	
}

SomNeuron* SomNetwork::findWinning(const std::vector<double> &vec){
	
  SomNeuron* winner = NULL;

  double LowestDistance = 999999;
 
  for (int n = 0; n < neurons.size(); n++){
  	
    double dist = neurons[n].calculateDistance(vec);

    if (dist < LowestDistance){
      LowestDistance = dist;
      winner = &neurons[n];
    }
  }

  return winner;
}

bool SomNetwork::saveWeights(std::string filename){

	if (neurons.size() == 0)
		return false;

	std::ofstream file(filename.c_str());
	
	std::cout << "salvando arquivo " << std::endl;
	for (int i = 0; i < neurons.size(); i++){
			//std::cout << neurons[i].getX() << " " << neurons[i].getY() << std::endl;
			std::vector<double> weight;
			neurons[i].getWeight(weight);
			file << neurons[i].getX() << " " << neurons[i].getY() << " ";
			for(unsigned int k = 0; k < weight.size(); k++)
				file << (int)(weight[k]*255) << " ";
			file << " " << std::endl; 
	}
	
	file.close();
	return true;
}
