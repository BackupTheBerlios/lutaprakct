#ifndef REPRODUCTION_H_
#define REPRODUCTION_H_

#include "../layer.h"

class ReproductionLayer : public Layer{
	
	public:
		
		ReproductionLayer(){};
		virtual ~ReproductionLayer(){};
		
		void run(SubsumptionAgentData* data, void* auxiliarData);
	
};

#endif /*REPRODUCTION_H_*/
