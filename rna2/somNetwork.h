#ifndef SOMNETWORK_H_
#define SOMNETWORK_H_

#include "somNeuron.h"
#include <vector>

class SomNetwork{
	
	public:

		SomNetwork() : winning(NULL), radius(0), timeConstant(0), numIterations(0), iterationCount(0),
						neighbourhoodRadius(0), influence(0), learningRate(0), done(false) {};
	
		bool initialize(int sizex, int sizey, int iterations, int inputVectorSize);
		
		bool train(const std::vector<std::vector<double> > &data);
	
		bool saveWeights(std::string filename);
	
	private:
	
		std::vector<SomNeuron> neurons;
		
		SomNeuron* findWinning(const std::vector<double>& v);
		
		SomNeuron* winning;
		double              radius;
  		double              timeConstant;
  		int                 numIterations;
		int                 iterationCount;
  		double              neighbourhoodRadius;
		double              influence;
		double              learningRate;
		int numFirstNeurons;
		int sizex, sizey;
		bool                done;

	
};

#endif /*SOMNETWORK_H_*/
