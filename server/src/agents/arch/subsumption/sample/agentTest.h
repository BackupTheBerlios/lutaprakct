#ifndef AGENTTEST_H_
#define AGENTTEST_H_

#include "../subsumptionagent.h"
#include <iostream>

class AgentTest : public SubsumptionAgent {
	
	public:
		
		AgentTest(){ internalData = NULL; specificAgentData = NULL; };
		virtual ~AgentTest(){ shutdown(); };
			
		bool initialize(char* filename);
		void afterRun();
		void beforeRun();
	
		int getPositionX();
		int getPositionY();
		void setPositionX(int x);
		void setPositionY(int y);
		
		void setScreenPositionX(int x);
		void setScreenPositionY(int y);
		
		void pickColor();
		
		int getCor();
		int getGene0();
		int getGene1();
		void setGene0(int gen);
		void setGene1(int gen);
		
		int getId();
		void setId(int id);
	
};


#endif /*AGENTTEST_H_*/
