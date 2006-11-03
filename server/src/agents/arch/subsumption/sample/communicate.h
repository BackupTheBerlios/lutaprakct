#ifndef COMMUNICATE_H_
#define COMMUNICATE_H_

#include "../layer.h"

class CommunicateLayer : public Layer{
	
	public:
		
		CommunicateLayer(){};
		virtual ~CommunicateLayer(){};
		
		void run(SubsumptionAgentData* data, void* auxiliarData);
	
};



#endif /*COMMUNICATE_H_*/
