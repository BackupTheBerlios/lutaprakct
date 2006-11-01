#ifndef TESTAGENTDATA_H_
#define TESTAGENTDATA_H_

#include <vector>
#include "agentTest.h"

class TestAgentData{
	
	public:
		TestAgentData(){visionrange = 4;};
		virtual ~TestAgentData(){};
		
		int posx, posy;
		int visionrange;
		int id;
		int alvoid;
		
		bool alvoAtivo;
		bool alvo;
		bool direcoes[8]; 
		bool caminhos[8];
		
		std::vector<AgentTest*> targets;
};

#endif /*TESTAGENTDATA_H_*/
