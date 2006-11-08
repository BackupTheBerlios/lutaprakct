#ifndef TESTAMBIENT_H_
#define TESTAMBIENT_H_

#include "../ambient.h"
#include "../../../util/patterns/singleton.h"
#include "../../arch/subsumption/sample/agentTest.h"
#include <map>


template <class T>
class TestAmbient : public Ambient<T>{
	
	public:
	
		TestAmbient(){idcounter = 0;};
		virtual ~TestAmbient(){};
		
		bool initialize(char* filename){return true;};
		void shutdown(){};
		void run(){};
		
		std::map<int, int > msgs;
		
		int getLastId(){ idcounter++; return idcounter; };
		
	private:
		
		int idcounter;
};

typedef singleton < TestAmbient <AgentTest*> > AMBIENT;

#endif /*TESTAMBIENT_H_*/
