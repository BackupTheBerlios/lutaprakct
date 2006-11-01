#ifndef TESTAMBIENT_H_
#define TESTAMBIENT_H_

#include "../ambient.h"
#include "../../../util/patterns/singleton.h"
#include "../../arch/subsumption/sample/agentTest.h"

template <class T>
class TestAmbient : public Ambient<T>{
	
	public:
	
		TestAmbient(){};
		virtual ~TestAmbient(){};
		
		bool initialize(char* filename){return true;};
		void shutdown(){};
		void run(){};
		
	
};

typedef singleton < TestAmbient <AgentTest*> > AMBIENT;

#endif /*TESTAMBIENT_H_*/
