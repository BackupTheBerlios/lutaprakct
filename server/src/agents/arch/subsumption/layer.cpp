
#include "layer.h"

Layer::Layer(){
}

Layer::~Layer(){
}

void Layer::setId(int id){
	this->id = id;
}

int Layer::getId(){
	return id;
}

void Layer::subsume(SubsumptionAgentData* data){ 
	data->initializeSubsumption(id); 
}

void Layer::endSubsume(SubsumptionAgentData* data){ 
	data->endSubsumption(); 
}
