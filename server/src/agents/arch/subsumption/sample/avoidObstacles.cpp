
#include "avoidObstacles.h"
#include "agentTest.h"
#include "testAgentData.h"
#include <iostream>

void AvoidObstaclesLayer::run(SubsumptionAgentData* data, void* auxiliarData){
	
	TestAgentData* agentData = static_cast<TestAgentData*>(auxiliarData);
	std::cout << "evitanto obstaculos " << std::endl;
   //se o alvo ainda esta no campo de visao
	if (agentData->alvo) {
		//std::cout<< "escolhendo camiho ate o alvo" << std::endl;
		int distx, disty;
		distx =   agentData->posx - agentData->alvox ;	   
		disty = agentData->posy - agentData->alvoy  ;
		int absdistx = abs(distx);
		int absdisty = abs(disty);
		if ( (absdistx > 1) || (absdisty > 1) ){
	   	//std::cout << "EVITAR x: " << e->posx << 
		//	" y: " << e->posy << std::endl;
	    //std::cout << "EVITAR alvox: " << e->alvox << " alvoy: " << e->alvoy << std::endl;
	    //std::cout << "EVITAR distx: " << distx << " disty: " << disty << std::endl;
	    //verifica em que dire????ao o alvo esta
		if ( ((distx >= 1) && (disty >= 1)) && (agentData->direcoes[0] == true) )
			agentData->caminhos[0] = true;
		if ( ((distx == 0) && (disty >= 1)) && (agentData->direcoes[1] == true) )
			agentData->caminhos[1] = true;	
		if ( (distx <= -1) && (disty >= 1) && (agentData->direcoes[2] == true) )
			agentData->caminhos[2] = true;
		if ( (distx <= -1) && (disty == 0) && (agentData->direcoes[3] == true) )
			agentData->caminhos[3] = true;
		if ( (distx <= -1) && (disty <= -1)  && (agentData->direcoes[4] == true) )
			agentData->caminhos[4] = true;
		if ( (distx == 0) && (disty <= -1)  && (agentData->direcoes[5] == true)) 
			agentData->caminhos[5] = true;
		if ( (distx >= 1) && (disty <= -1) && (agentData->direcoes[6] == true) )
			agentData->caminhos[6] = true;
		if ( (distx >= 1) && (disty == 0) && (agentData->direcoes[7] == true) )
			agentData->caminhos[7] = true;
	}
	//	distx = abs(distx);
	//	disty = abs(disty);
	/*	if ( (distx == 1) && (disty == 1) ){
			for (unsigned int i = 0; i<8; i++)
				e->caminhos[i] = false;			
		}*/
	}
	else {

		//std::cout << "escolhendo caminho randomico" << std::endl;
		int j=0;
		std::vector<int> caminhorandomico;
		for (int k = 0; k <= 8; k++){
			if (agentData->direcoes[k] == true){
				   j++;
				   caminhorandomico.push_back(k);
			}
		}
		if (j){
			int m = rand()%j;
			if (agentData->direcoes[caminhorandomico[m]]){
				agentData->caminhos[caminhorandomico[m]] = true;	
			}
		}
	}

	for (unsigned int i = 0; i<8; i++)
		agentData->direcoes[i] = true;

	
}


