
#include "subsumptionagent.h"
#include <iostream>

//TODO carregar os scriprs em lua
bool SubsumptionAgent::initialize(char* filename){
	
	return true;
}

void SubsumptionAgent::shutdown(){
	if (internalData)
		delete internalData;
}

void SubsumptionAgent::beforeRun(){

	return;
}

void SubsumptionAgent::afterRun(){
	
	std::cout << "subsumption agent" << std::endl;
	return;	
}

void SubsumptionAgent::run(){

	beforeRun();

	if (isRunning()){

		if (!layers.empty())	{
			for (unsigned int i = 0; i < layers.size(); i++){
				if (internalData){
					 //se nenhuma camada esta subordinando executa todas as camadas
					if (!internalData->hasLayerSuming())
						layers[i]->run(internalData, specificAgentData);
					else 
						//se alguma camada esta subordinando so executa a subordinadora
						if (internalData->getLayerSumingId() == layers[i]->getId() )
							layers[i]->run(internalData, specificAgentData);
				}
			}
		}else//se os layers estao vazios
			return;
		
	}else{//se esta pausado
		return;
	}
	
	afterRun();
	
}
