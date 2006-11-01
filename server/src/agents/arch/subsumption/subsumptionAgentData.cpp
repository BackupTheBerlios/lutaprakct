
#include "subsumptionAgentData.h"

SubsumptionAgentData::SubsumptionAgentData(){
	layerSuming = false;
}

SubsumptionAgentData::~SubsumptionAgentData(){
}

bool SubsumptionAgentData::hasLayerSuming(){
	return layerSuming;
}

int SubsumptionAgentData::getLayerSumingId(){
	return layerSumingId; 
}
