#include "communicate.h"
#include "agentTest.h"
#include "testAgentData.h"
#include "../../../ambient/sample/testAmbient.h"
#include <iostream>

void CommunicateLayer::run(SubsumptionAgentData* data, void* auxiliarData){
	
	TestAgentData* agentData = static_cast<TestAgentData*>(auxiliarData);
	std::cout << "comunicando " << std::endl;
	
	if (agentData->alvoid){
		if ( AMBIENT::getInstance().msgs[agentData->id] == agentData->alvoid ){
			agentData->resposta = true;
			 //std::cout << "COMUNICAR resposta chegou: " << msgs[e->id] << "alvoid " << e->alvoid  << std::endl;
		}
	
		if(!agentData->resposta){ //nao teve resposta ainda
				//std::cout << "COMUNICAR nao tem resposta " << std::endl;
				if (!agentData->pedido){ //mas nao enviou pedido
					int key = agentData->alvoid;
					int alvo = agentData->id;
					AMBIENT::getInstance().msgs[key] = alvo;
					agentData->pedido = true;
				//	std::cout << "COMUNICAR enviou pedido" << std::endl;
				}
		}else{
			if (!agentData->pedido){
			//	std::cout << "COMUNICAR tem resposta masn ao tem pedido" << std::endl;
				AMBIENT::getInstance().msgs[agentData->alvoid] = agentData->id;
				agentData->pedido = true;
			}
		
		}
	}
	
}
