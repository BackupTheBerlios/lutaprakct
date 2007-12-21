#ifndef SKYNETNEURON_H_
#define SKYNETNEURON_H_

#include <vector>
#include <cmath>
#include "SkyNeuronConnection.h"

class SkyNeuron{
	
	public:
		SkyNeuron(){};
		SkyNeuron(int numWeights){ initialize(numWeights); };
		~SkyNeuron(){ weights.clear(); };
		
		void initialize(int numWeights){
			for (int w = 0; w < numWeights*2; w++)
      			weights.push_back((rand())/(RAND_MAX+1.0));
      		numWeights++;
      		while ( numWeights --> 0)
      			habituationWeights.push_back(1.0);
		};
		
		double calculateDistance(const std::vector<double>& v){
			
			double distance = 0;
  
			for (unsigned int i=0; i < weights.size(); i++)
    			distance += ( v[i] - weights[i]) * (v[i] - weights[i]);

			return sqrt(distance);
		}
		
		bool hasConnection(SkyNeuronConnection<SkyNeuron*>* n){
			
			for (unsigned int i = 0; i < connections.size(); i++)
				if (connections[i] == n)
					return true;
					
			return false;
				
		}
		
		bool hasConnectionWith(SkyNeuron* n){
			for (unsigned int i = 0; i < connections.size(); i++)
				if ( ( (connections[i]->a  == n) || (connections[i]->b == n) )  )
					return true;
					
			return false;	
		}
		
		void addConnection(SkyNeuronConnection<SkyNeuron*>* n){
			connections.push_back(n);
		}
		
	private:
	
		std::vector<double> weights;
		std::vector<double> habituationWeights;
		
		std::vector< SkyNeuronConnection<SkyNeuron* >* > connections;
	
};

#endif /*SKYNETNEURON_H_*/
