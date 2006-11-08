
#include "lookaround.h"
#include "../../../ambient/sample/testAmbient.h"
#include "agentTest.h"
#include "testAgentData.h"
#include <iostream>

void LookAroundLayer::run(SubsumptionAgentData* data, void* auxiliarData){

	TestAgentData* agentData = static_cast<TestAgentData*>(auxiliarData);
	
	if ( (abs( agentData->posx - agentData->alvox) <= 1) && ( abs(agentData->posy - agentData->alvoy) <= 1) ){
	//	std::cout << "REPRODUZINDO esta proximo do alvo" << std::endl;
		if (!agentData->reproduzindo){ //nao esta reproduzindo
			if(!agentData->resposta){ //nao teve resposta ainda
			//	std::cout << "REPRODUZINDO nao tem resposta " << std::endl;
				if (agentData->pedido){
					agentData->espera_reproducao++;
					if (agentData->espera_reproducao >= agentData->wait){ //desiste
						AMBIENT::getInstance().msgs.erase(agentData->id);
						agentData->reproduzindo = false;
						agentData->alvo = false;
						agentData->pedido = false;
						agentData->resposta = false;
						agentData->alvoid = 0;
						agentData->alvox = 0;
						agentData->alvoy = 0;
						agentData->turnos = 1;
						agentData->alvogenes[0] = 0;
						agentData->espera_reproducao = 0;
						agentData->alvogenes[1] = 0;
					}
				}
			}else{ //se ja recebeu a resposta muda pra reproduzindo
				if (agentData->pedido){ //e ja enviou pedido entao ta reproduzindo
					if (agentData->resposta){
					//	std::cout << "REPRODUZINDO iniciar reproducao" << std::endl;
						agentData->reproduzindo = true;
					}
				}
			}
		}else{ //esta reproduzindo e recebeu a resposta cria o filho
			//std::cout << "REPRODUZINDO e->id: " << e->id << " alvoid " << e->alvoid << std::endl;
			if (agentData->id < agentData->alvoid){
				std::vector<unsigned int> posicoesRand;
				for(int i = 0; i < 8; i++){
					if (agentData->direcoes[i] != false){
						posicoesRand.push_back(i);
					//	std::cout << "direcao falsa: " << i << std::endl;
					}
				}
				int div = posicoesRand.size();
				//std::cout << "div: " << div << std::endl;
				int semespaco = 0;
				if (div == 0){
					div = 2;
					semespaco = 1;
				}
				
				//std::cout << "indice: " << indice << std::endl;
				//std::cout << "escolha: " << escolha << std::endl;
				if (!semespaco){
					int indice = rand()%(div);
					int escolha = posicoesRand[indice];		
					if (agentData->direcoes[escolha] != false){
					//	std::cout << "CRIOU ENTIDADE" << std::endl;	
						AgentTest* novo;
						novo = new AgentTest();
						int x, y;
						x = agentData->x;
						y = agentData->y;
						if (escolha == 0){
							x -= 10;
							y -= 10;
						}else if (escolha == 1){
							y = y-10;
						}else if ( escolha == 2){
							x = x+10;
							y = y-10;
						}else if (escolha == 3){
							x = x+10;
						}else if (escolha == 4){
							x = x+10;
							y = y+10;
						}else if (escolha == 5){
							y = y+10;
						}else if ( escolha == 6){
							x = x-10;
							y = y+10;
						}else if (escolha == 7){
							x = x-10;
		
						}		
					    novo->setx(x);
						novo->sety(y);
						novo->posx = x/10;
						novo->posy = y/10;
						
						if ( (rand()%100 +1) <= 50 ){ //pega o gene[0] do pai
							novo->genes[0] = agentData->genes[0];
						}else{
							novo->genes[0] = agentData->genes[1];
						}
						  
						if ( (rand()%100+1) <= 50) {
							novo->genes[1] = agentData->alvogenes[0];
						}else{
							novo->genes[1] = agentData->alvogenes[1];
						}

						if ( (novo->genes[0] <= 101) && (novo->genes[1] <= 101) ){
							novo->determinaCor();
						//std::cout << "CRIOU NOVO EM: x " << x << " y " << y << " gene0 " << novo[0]->genes[0] << " gene1 " << novo[0]->genes[1]  <<  std::endl;
							novo->setId(idcounter);
							AMBIENT::getInstance().addAgent(novo);
						//births++;
						//idcounter++;
							AMBIENT::getInstance().msgs.erase(agentData->id);
							agentData->reproduzindo = false;
							agen	tData->alvo = false;
							agentData->pedido = false;
							agentData->resposta = false;
							agentData->alvoid = 0;
							agentData->alvox = 0;
							agentData->alvoy = 0;
							agentData->turnos = 1;
							agentData->alvogenes[0] = 0;
							agentData->alvogenes[1] = 0;
							novo->status = 0;
						//novo[0]->thread = SDL_CreateThread( (*doAction), (void*) novo[0]);
						//if (novo[0]->thread == NULL){
							//trace("#ERROR: Unable to create thread.");
							//entidades.remove(novo[0]);
						//}
						//}else{
						//	trace("#ERROR: invalid gen ( > 100).");
						}
					
					}
			 	}
			}
			
			AMBIENT::getInstance().msgs.erase(e->id);
			agentData->reproduzindo = false;
			agentData->alvo = false;
			agentData->pedido = false;
			agentData->resposta = false;
			agentData->alvoid = 0;
			agentData->alvox = 0;
			agentData->alvoy = 0;
			agentData->alvogenes[0] = 0;
			agentData->alvogenes[1] = 0;
			agentData->espera_reproducao = 0;
			agentData->turnos = 1;
		}
		
		
	}
	
	
}

