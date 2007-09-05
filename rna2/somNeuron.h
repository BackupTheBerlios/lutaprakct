#ifndef SOMNEURON_H_
#define SOMNEURON_H_

#include <vector>
#include <cmath>
#include <iostream>

class SomNeuron{
	
	public:
	
		SomNeuron( int numWeights) {
			
			for (int w = 0; w < numWeights; w++)
      			weights.push_back((rand())/(RAND_MAX+1.0));
			
		};
		
		double calculateDistance(const std::vector<double>& v){
			double distance = 0;
  
			for (unsigned int i=0; i < weights.size(); i++)
    			distance += ( v[i] - weights[i]) * (v[i] - weights[i]);

			//return sqrt(distance);
			return distance;
		}
		
		void adjustWeights(const std::vector<double> &target, const double LearningRate, const double Influence){
			for (unsigned int w = 0; w < target.size(); w++)
    			weights[w] += LearningRate * Influence * (target[w] - weights[w]);
		}
		
		void getWeight(std::vector<double>& v){
			for (unsigned int i = 0; i < weights.size(); i++){
				v.push_back(weights[i]);
			}
		}
		
		int getX(){return x;};
		int getY(){return y;};
		void setX(int x){this->x = x;}
		void setY(int y){this->y = y;}
		
	private:
	
		std::vector<double> weights;
		int x, y;
	
};

#endif /*SOMNEURON_H_*/
