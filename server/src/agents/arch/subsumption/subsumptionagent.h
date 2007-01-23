#ifndef SUBSUMPTIONAGENT_H_
#define SUBSUMPTIONAGENT_H_

#include <vector>
#include "../../agent.h"
#include "layer.h"
#include "subsumptionAgentData.h"

class SubsumptionAgent : public Agent {
	
	public:
		
		SubsumptionAgent(){internalData = NULL;};
		virtual ~SubsumptionAgent(){shutdown();};
			
		bool initialize(char* filename);
		void shutdown();
		void run();
		void afterRun();
		void beforeRun();	
	
	protected:
	
		std::vector<Layer*> layers;
		SubsumptionAgentData* internalData;
	
};

#endif /*SUBSUMPTIONAGENT_H_*/
