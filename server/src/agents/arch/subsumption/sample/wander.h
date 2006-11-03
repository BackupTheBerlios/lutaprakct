#ifndef WANDER_H_
#define WANDER_H_

#include "../layer.h"

class WanderLayer : public Layer{
	
	public:
		
		WanderLayer(){};
		virtual ~WanderLayer(){};
		
		void run(SubsumptionAgentData* data, void* auxiliarData);
	
};

#endif /*WANDER_H_*/
