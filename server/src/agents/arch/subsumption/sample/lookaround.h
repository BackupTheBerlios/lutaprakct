#ifndef LOOKAROUNDLAYER_H_
#define LOOKAROUNDLAYER_H_

#include "../layer.h"

class LookAroundLayer : public Layer {
	
	public:
		
	LookAroundLayer(){};
	virtual ~LookAroundLayer(){};
	
	void run(SubsumptionAgentData* data, void* auxiliarData);
	
};

#endif /*LOOKAROUNDLAYER_H_*/
