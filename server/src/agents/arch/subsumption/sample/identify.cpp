
#include "identify.h"
#include "agentTest.h"
#include "testAgentData.h"
#include <iostream>
#include <vector>
#include <algorithm>

void IdentifyLayer::run(SubsumptionAgentData* data, void* auxiliarData){
	
	TestAgentData* agentData = static_cast<TestAgentData*>(auxiliarData);
	
	std::cout << "identificando" << std::endl;
	
	/* vetor de indice eh o vetor de cordoalvo-cordoagente
	 * depois eh dado um sort nesse vetor
	 * */
	std::vector<int> indices;
	for (unsigned int i = 0; i < (agentData->targets).size(); i++){
		int indice = abs(agentData->cor - (agentData->targets[i])->getCor());
		indices.push_back(indice);
	}

	unsigned int alvos = agentData->targets.size();
	
	if (alvos > 0){
		std::sort( indices.begin(), indices.end());
		//seleciona o escolhido
		//std::cout << "IDENTIFICAR indice 0 " << indices[0] << std::endl;
		std::vector<AgentTest*> possibilidades;
		//cor aceita eh a cor do indice 0 depois do sort
		int coraceita = indices[0];
		
		//cria o vetor de possibilidade, com todos os targets com a cor aceita	
		for (unsigned int k = 0; k < alvos; k++){
			if (coraceita == abs(agentData->cor - (agentData->targets[k])->getCor()) ){
				possibilidades.push_back(agentData->targets[k]);
			}
		}
		
		//pega um qualquer do vetor
		int randalvo = rand()%(possibilidades.size());
		agentData->alvo = true;
		agentData->alvox = (agentData->targets[randalvo])->getPositionX();	
		agentData->alvoy = (agentData->targets[randalvo])->getPositionY();
		agentData->alvoid = (agentData->targets[randalvo])->getId();
		agentData->alvogenes[0] = (agentData->targets[randalvo])->getGene0();	
		agentData->alvogenes[1] = (agentData->targets[randalvo])->getGene1();

		//std::cout << "IDENTIFICAR " << "alvox " << e->alvox << "alvoy " << e->alvoy <<  " alvoid " << e->alvoid << " (e->targets[randalvo])->id " << (e->targets[randalvo])->id << std::endl;
		//std::cout << " alvogene0 " << (e->targets[randalvo])->genes[0] << " alvogene1 " << (e->targets[randalvo])->genes[1] << std::endl; 
		}else{
			agentData->alvo = false;
		}
	
}
