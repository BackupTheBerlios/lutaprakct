#ifndef TESTAGENTDATA_H_
#define TESTAGENTDATA_H_

#include <vector>
#include "agentTest.h"

class TestAgentData{
	
	public:
		TestAgentData(){
			visionrange = 0; //setar
			reproduzindo = false;
			alvo = false;
			alvoid = 0;
			posx = posy = x = y = 0; //setar
			genes[0] = genes[1] = 0; //setar
			cor = 0; //setar
			espera_reproducao = 0;
			wait = 0;
			turnos = 0;
			vida = 0;
			
			alvox = alvoy = alvoid = 0;
			alvogenes[0] = alvogenes[1] = 0;
			
			resposta = false;
			pedido = false;
			
			for (unsigned int i = 0; i<8; i++){
				direcoes[i] = false;
				caminhos[i] = false;
			}
			
		};
		virtual ~TestAgentData(){};
		
		//caracteristicas do agente
		int posx, posy;
		int x, y;
		int visionrange;
		int id;
		int genes[2];
		int cor;
		int rgbColor[3];
		int espera_reproducao;
		int wait;
		int turnos;	
		int vida;
			
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
