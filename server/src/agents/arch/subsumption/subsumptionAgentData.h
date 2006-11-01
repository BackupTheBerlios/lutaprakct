#ifndef SUBSUMPTIONAGENTDATA_H_
#define SUBSUMPTIONAGENTDATA_H_

#include "../../agentData.h"
#include <vector>

class SubsumptionAgentData : public AgentData{
	
	public:
	
		SubsumptionAgentData();
		virtual ~SubsumptionAgentData();
		
		bool hasLayerSuming();
		int getLayerSumingId();
		
		void initializeSubsumption(int id){ layerSuming = true; layerSumingId = id;};
		void endSubsumption(){ layerSuming = false;};
		
	private:
	
		bool layerSuming;
		int layerSumingId;
	
};

#endif /*SUBSUMPTIONAGENTDATA_H_*/
