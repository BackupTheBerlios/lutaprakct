
#include "lookaround.h"
#include "../../../ambient/sample/testAmbient.h"
#include "agentTest.h"
#include "testAgentData.h"
#include <algorithm>

#include <list>
#include <iostream>

void LookAroundLayer::run(SubsumptionAgentData* data, void* auxiliarData){

	TestAgentData* agentData = static_cast<TestAgentData*>(auxiliarData);
	std::list<AgentTest*> *lista = AMBIENT::getInstance().getAgents();
	
	if (lista == NULL)
		std::cout << "sem agentes no campo de visao" << std::endl;
	
	int x, y;
	int absdistx, absdisty;
	int distx, disty;
	
	std::list<AgentTest*>::iterator entityiter;
	
	//verifica quais agentes tao no campo de visao e como estao
	//os espacos ao redor do agente
	if (lista){
		for (entityiter = lista->begin(); entityiter != lista->end() ; entityiter++){
			if ( (abs( (*entityiter)->getPositionX() - (agentData->posx) ) <= agentData->visionrange) &&  (abs( (*entityiter)->getPositionY() - (agentData->posy) ) <= agentData->visionrange)){ 
				if( (*entityiter)->getId() != agentData->id){
					//verifica se ja existe o target
					bool add = true;
					int entityid = (*entityiter)->getId(); 
					for (unsigned int i = 0; i < agentData->targets.size(); i++){
						int targid = agentData->targets[i]->getId(); 
						if ( entityid == targid ){
							add = false;
							break;
						}
					}
					if ( add ){
						agentData->targets.push_back( (*entityiter) );
						std::cout << "target adicionado " << agentData->targets.size() << std::endl;
					}	
					x = (*entityiter)->getPositionX();
					y = (*entityiter)->getPositionY();
					distx = agentData->posx - x;
					disty = agentData->posy - y;
					absdistx = abs(distx);
					absdisty = abs(disty);
					if ( ( absdistx <= 1) && ( absdisty <= 1)){ //se a distancia ate o alvo for menor q 1
						//verifica qual dire????ao esta ocupada pelo alvo
						//std::cout << "distx: " << distx << " disty: " << disty << std::endl;
						if ( (distx == 1) && (disty == 1) )
							agentData->direcoes[0] = false;
						if ( (distx == 0) && (disty == 1))
							agentData->direcoes[1] = false;
						if ( (distx == -1) && (disty == 1))
							agentData->direcoes[2] = false;
						if ( (distx == -1) && (disty == 0) )
							agentData->direcoes[3] = false;
						if ( (distx == -1) && (disty == -1) )
							agentData->direcoes[4] = false;
						if ( (distx == 0) && (disty == -1) ) 
							agentData->direcoes[5] = false;
						if ( (distx == 1) && (disty == -1) )
							agentData->direcoes[6] = false;
						if ( (distx == 1) && (disty == 0) )
							agentData->direcoes[7] = false;
					}
				}
			}
		}
	}
	
	//colisao com os limites do mapa
	if( agentData->posx == 0){
		agentData->direcoes[0] = false;
		agentData->direcoes[1] = false;
		agentData->direcoes[2] = false;
	}
	if( agentData->posy == 59){
		agentData->direcoes[4] = false;
		agentData->direcoes[5] = false;
		agentData->direcoes[6] = false;
	}
	if( agentData->posx == 0){
		agentData->direcoes[0] = false;
		agentData->direcoes[6] = false;
		agentData->direcoes[7] = false;
	}
	if( agentData->posx == 79){
		agentData->direcoes[2] = false;
		agentData->direcoes[3] = false;
		agentData->direcoes[4] = false;
	}
	
	//essa parte apenas procura pelo alvo dentro do vector
	//targets que o agente escolheu. no caso ele procura
	// pelo id. se nao achar o alvoAtivo fica false e 
	//o agente vai procurar outro alvo depois.
	if (agentData->targets.size()){ //se tiver algum alvo perto, entao ele pode ser um obstaculo
		bool alvoAtivo = false;
		for (unsigned int i = 0; i < agentData->targets.size(); i++){
			if ((agentData->targets[i])->getId() == agentData->alvoid){ //verifica se o alvo ainda esta na linha de visao
			//	std::cout << "OBSERVAR alvoid " << e->alvoid << " e->targets[i]->id " << (e->targets[i])->id << std::endl;
				agentData->alvoAtivo = true;
				//e->alvox = (e->targets[i])->posx;
				//e->alvoy = (e->targets[i])->posy;
				//e->alvo = true;
			}
		}
		if (!alvoAtivo){
			agentData->alvo = false;
			agentData->alvoid = 0;
		}
	}
	
}

