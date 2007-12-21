#ifndef SKYNET_H_
#define SKYNET_H_

#include "SkyNeuron.h"
#include <vector>

class TemporalMemory{
	
	public:
	
		std::vector<double> x; //x-1
		std::vector<double> y; //y-1
		
		virtual ~TemporalMemory(){
			x.clear();
			y.clear();
		}
		TemporalMemory(){};
		TemporalMemory(int size): size(size){
			size++;
			while( size --> 0){
				x.push_back(0);
				y.push_back(0);
			}
		};
		
		void calculate(std::vector<double>& in, std::vector<double>& outx, std::vector<double>& outy ){
			
			for (unsigned int i = 0; i < in.size(); i++)//calculate x
				outx.push_back((1-u)*in[i] + u*x[i]);
				
			for (unsigned int i = 0; i < in.size(); i++)//calculate y
				 outy.push_back( ((1-n)*(in[i]-x[i])) + n*y[i] );
				 
			for (unsigned int i = 0; i < in.size(); i++){
				x[i] = outx[i];
				y[i] = outy[i];
			}
				
		};	
	
		double u, n;
		int size; //size of the vectors
};

class SkyNet{
	
	public:
	
		SkyNet(){};
		
		bool initialize();
	
		std::vector<SkyNeuron*> findWinnings(const std::vector<double>& v);
		void initializeConnections( std::vector<SkyNeuron*>& n);
		
		void adjustHabituations();
		
		
		std::vector<SkyNeuron> neurons;
	
		int maxNeurons;
		int maxConnections;
		int maxConnectionAge;
		double plasticity;
		double novelty;
	
};

#endif /*SKYNET_H_*/
