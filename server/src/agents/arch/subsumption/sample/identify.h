#ifndef IDENTIFYLAYER_H_
#define IDENTIFYLAYER_H_

#include "../layer.h"

class IdentifyLayer : public Layer{
	
	public:
		
		IdentifyLayer(){};
		virtual ~IdentifyLayer(){};
		
		void run(SubsumptionAgentData* data, void* auxiliarData);
	
};

#endif /*IDENTIFYLAYER_H_*/
