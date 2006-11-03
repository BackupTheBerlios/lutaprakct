#ifndef AVOIDOBSTACLES_H_
#define AVOIDOBSTACLES_H_

#include "../layer.h"

class AvoidObstaclesLayer : public Layer{
	
	public:
		
		AvoidObstaclesLayer(){};
		virtual ~AvoidObstaclesLayer(){};
		
		void run(SubsumptionAgentData* data, void* auxiliarData);
	
};

#endif /*AVOIDOBSTACLES_H_*/
