
#include "agentTest.h"
#include "lookaround.h"
#include "identify.h"
#include "testAgentData.h"

bool AgentTest::initialize(char* filename){

	LookAroundLayer* observar = new LookAroundLayer();
	observar->setId(1);
	layers.push_back(observar);
		
	IdentifyLayer* identificar = new IdentifyLayer();
	identificar->setId(2);
	layers.push_back(identificar);
	
	internalData = new SubsumptionAgentData();
	specificAgentData =  new TestAgentData();
	
	return true;
}

int AgentTest::getPositionX(){
	if (specificAgentData)
		return (static_cast<TestAgentData*>(specificAgentData))->posx;
	else
		return -1;
}

int AgentTest::getPositionY(){
	if (specificAgentData)
		return (static_cast<TestAgentData*>(specificAgentData))->posy;
	else
		return -1;
}

void AgentTest::setPositionX(int x){
	if (specificAgentData)
		(static_cast<TestAgentData*>(specificAgentData))->posx = x;
	else
		return;
}

void AgentTest::setPositionY(int y){
	if (specificAgentData)
		(static_cast<TestAgentData*>(specificAgentData))->posy = y;
	else
		return;
}

int AgentTest::getId(){
	if (specificAgentData)
		return (static_cast<TestAgentData*>(specificAgentData))->id;
	else
		return -1;	
}

void AgentTest::setId(int id){

	if (specificAgentData)
		(static_cast<TestAgentData*>(specificAgentData))->id = id;
	
}
