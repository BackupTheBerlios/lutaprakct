
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

int AgentTest::getCor(){
	if (specificAgentData)
		return (static_cast<TestAgentData*>(specificAgentData))->cor;
	else
		return -1;	
}

int AgentTest::getGene0(){
	if (specificAgentData)
		return (static_cast<TestAgentData*>(specificAgentData))->genes[0];
	else
		return -1;	
}

int AgentTest::getGene1(){
	if (specificAgentData)
		return (static_cast<TestAgentData*>(specificAgentData))->genes[1];
	else
		return -1;	
}

void AgentTest::setId(int id){

	if (specificAgentData)
		(static_cast<TestAgentData*>(specificAgentData))->id = id;
	
}
