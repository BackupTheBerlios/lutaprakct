#ifndef TESTAGENTDATA_H_
#define TESTAGENTDATA_H_

#include <vector>
#include "agentTest.h"

class TestAgentData{
	
	public:
		TestAgentData(){visionrange = 4;};
		virtual ~TestAgentData(){};
		
		//caracteristicas do agente
		int posx, posy;
		int x, y;
		int visionrange;
		int id;
		int genes[2];
		int cor;
		int espera_reproducao;
		int wait;
		int turnos;	
			
		//caracteristicas do alvo do agente
		int alvogenes[2];
		bool alvo;
		int alvoid;
		int alvox;
		int alvoy;
		
		//outras variaveis usadas pelas competencias
		bool direcoes[8]; 
		bool caminhos[8];
		bool resposta;
		bool pedido;
		bool reproduzindo;
		
		std::vector<AgentTest*> targets;
};

#endif /*TESTAGENTDATA_H_*/
