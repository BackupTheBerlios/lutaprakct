#ifndef AGENTTEST_H_
#define AGENTTEST_H_

#include "../subsumptionagent.h"

class AgentTest : public SubsumptionAgent {
	
	public:
		
		AgentTest(){ internalData = NULL; specificAgentData = NULL; };
		virtual ~AgentTest(){ shutdown(); };
			
		bool initialize(char* filename);
	
		int getPositionX();
		int getPositionY();
		void setPositionX(int x);
		void setPositionY(int y);
		
		int getId();
		void setId(int id);
	
};


#endif /*AGENTTEST_H_*/
