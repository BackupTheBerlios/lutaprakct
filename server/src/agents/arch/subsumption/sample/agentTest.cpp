
#include "agentTest.h"
#include "lookaround.h"
#include "identify.h"
#include "testAgentData.h"
#include "avoidObstacles.h"
#include "wander.h"

bool AgentTest::initialize(char* filename){

	LookAroundLayer* observar = new LookAroundLayer();
	observar->setId(1);
	layers.push_back(observar);
		
	IdentifyLayer* identificar = new IdentifyLayer();
	identificar->setId(2);
	layers.push_back(identificar);
	
	AvoidObstaclesLayer* evitar = new AvoidObstaclesLayer();
	evitar->setId(3);
	layers.push_back(evitar);
	
	WanderLayer* vagar = new WanderLayer();
	vagar->setId(4);
	layers.push_back(vagar);
	
	internalData = new SubsumptionAgentData();
	specificAgentData =  new TestAgentData();
	
	pickColor();
	
	return true;
}

void AgentTest::afterRun(){
}

void AgentTest::beforeRun(){
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

void AgentTest::setScreenPositionX(int X){
	if (specificAgentData)
		(static_cast<TestAgentData*>(specificAgentData))->x = X;
	else
		return;
}

void AgentTest::setScreenPositionY(int Y){
	if (specificAgentData)
		(static_cast<TestAgentData*>(specificAgentData))->y = Y;
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

void AgentTest::setGene0(int gen){
	if (specificAgentData)
		(static_cast<TestAgentData*>(specificAgentData))->genes[0] = gen;
	else
		return;	
}

void AgentTest::setGene1(int gen){
	if (specificAgentData)
		(static_cast<TestAgentData*>(specificAgentData))->genes[1] = gen;
	else
		return;	
}

void AgentTest::setId(int id){

	if (specificAgentData)
		(static_cast<TestAgentData*>(specificAgentData))->id = id;
	
}

void AgentTest::pickColor(){
	
	if (!specificAgentData)
		return;
	
	TestAgentData* agentData = static_cast<TestAgentData*>(specificAgentData);
	
	agentData->cor = (agentData->genes[0] + agentData->genes[1])/2;
	switch(agentData->cor){
	
	case 1: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 0;					
		break;
	case 2: 
		agentData->rgbColor[0] = 60;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 0;					
		break;
	case 3: 
		agentData->rgbColor[0] = 90;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 0;					
		break;
	case 4: 
		agentData->rgbColor[0] = 120;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 0;					
		break;
	case 5: 
		agentData->rgbColor[0] = 150;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 0;					
		break;
	case 6: 
		agentData->rgbColor[0] = 180;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 0;					
		break;
	case 7: 
		agentData->rgbColor[0] = 210;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 0;					
		break;
	case 8: 
		agentData->rgbColor[0] = 240;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 0;					
		break;
	
	case 9: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 0;					
		break;
	case 10: 
		agentData->rgbColor[0] = 60;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 0;					
		break;
	case 11: 
		agentData->rgbColor[0] = 90;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 0;					
		break;
	case 12: 
		agentData->rgbColor[0] = 120;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 0;					
		break;
	case 13: 
		agentData->rgbColor[0] = 150;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 0;					
		break;
	case 14: 
		agentData->rgbColor[0] = 180;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 0;					
		break;
	case 15: 
		agentData->rgbColor[0] = 210;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 0;					
		break;
	case 16: 
		agentData->rgbColor[0] = 240;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 0;					
		break;

	
	case 17: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 30;					
		break;
	case 18: 
		agentData->rgbColor[0] = 60;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 30;					
		break;
	case 19: 
		agentData->rgbColor[0] = 90;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 30;					
		break;
	case 20: 
		agentData->rgbColor[0] = 120;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 30;					
		break;
	case 21: 
		agentData->rgbColor[0] = 150;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 30;					
		break;
	case 22: 
		agentData->rgbColor[0] = 180;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 30;					
		break;
	case 23: 
		agentData->rgbColor[0] = 210;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 30;					
		break;
	case 24: 
		agentData->rgbColor[0] = 240;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 30;					
		break;
	
	
	case 25: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 0;					
		break;
	case 26: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 60;
		agentData->rgbColor[2] = 0;					
		break;
	case 27: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 90;
		agentData->rgbColor[2] = 0;					
		break;
	case 28: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 120;
		agentData->rgbColor[2] = 0;					
		break;
	case 29: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 150;
		agentData->rgbColor[2] = 0;					
		break;
	case 30: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 180;
		agentData->rgbColor[2] = 0;					
		break;
	case 31: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 210;
		agentData->rgbColor[2] = 0;					
		break;
	case 32: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 240;
		agentData->rgbColor[2] = 0;					
		break;
	
	case 33: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 60;
		agentData->rgbColor[2] = 0;					
		break;
	case 34: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 90;
		agentData->rgbColor[2] = 0;					
		break;
	case 35: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 120;
		agentData->rgbColor[2] = 0;					
		break;
	case 36: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 150;
		agentData->rgbColor[2] = 0;					
		break;
	case 37: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 180;
		agentData->rgbColor[2] = 0;					
		break;
	case 38: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 210;
		agentData->rgbColor[2] = 0;					
		break;
/*	case 38: 
		rgbColor[0] = 30;
		rgbColor[1] = 240;
		rgbColor[2] = 0;					
		break;
*/
	
	case 39: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 30;					
		break;
	case 40: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 60;
		agentData->rgbColor[2] = 30;					
		break;
	case 41: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 90;
		agentData->rgbColor[2] = 30;					
		break;
	case 42: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 120;
		agentData->rgbColor[2] = 30;					
		break;
	case 43: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 150;
		agentData->rgbColor[2] = 30;					
		break;
	case 44: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 180;
		agentData->rgbColor[2] = 30;					
		break;
	case 45: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 210;
		agentData->rgbColor[2] = 30;					
		break;
	case 46: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 240;
		agentData->rgbColor[2] = 30;					
		break;
	
	
	case 47: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 30;					
		break;
	case 48: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 60;					
		break;
	case 49: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 90;					
		break;
	case 50: 
		agentData->rgbColor[0] = 250;
		agentData->rgbColor[1] = 250;
		agentData->rgbColor[2] = 250;					
		break;
	case 51: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 150;					
		break;
	case 52: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 180;					
		break;
	case 53: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 210;					
		break;
	case 54: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 240;					
		break;
	
	case 55: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 60;					
		break;
	case 56: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 90;					
		break;
	case 57: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 120;					
		break;
	case 58: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 150;					
		break;
	case 59: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 180;					
		break;
	case 60: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 210;					
		break;
	case 61: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 240;					
		break;
	
	case 62: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 60;					
		break;
	case 63: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 90;					
		break;
	case 64: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 120;					
		break;
	case 65: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 150;					
		break;
	case 66: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 180;					
		break;
	case 67: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 210;					
		break;
	case 68: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 0;
		agentData->rgbColor[2] = 240;					
		break;


	case 69: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 60;					
		break;
	case 70: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 90;					
		break;
	case 71: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 120;					
		break;
	case 72: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 150;					
		break;
	case 73: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 180;					
		break;
	case 74: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 210;					
		break;
	case 75: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 240;					
		break;
	
	case 76: 
		agentData->rgbColor[0] = 60;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 30;					
		break;
	case 77: 
		agentData->rgbColor[0] = 90;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 30;					
		break;
	case 78: 
		agentData->rgbColor[0] = 120;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 30;					
		break;
	case 79: 
		agentData->rgbColor[0] = 150;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 30;					
		break;
	case 80: 
		agentData->rgbColor[0] = 180;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 30;					
		break;
	case 81: 
		agentData->rgbColor[0] = 210;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 30;					
		break;
	case 82: 
		agentData->rgbColor[0] = 240;
		agentData->rgbColor[1] = 30;
		agentData->rgbColor[2] = 30;					
		break;
	
	case 83: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 60;
		agentData->rgbColor[2] = 30;					
		break;
	case 84:
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 90;
		agentData->rgbColor[2] = 30;					
		break;
	case 85: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 120;
		agentData->rgbColor[2] = 30;					
		break;
	case 86: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 150;
		agentData->rgbColor[2] = 30;					
		break;
	case 87: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 180;
		agentData->rgbColor[2] = 30;					
		break;
	case 88: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 210;
		agentData->rgbColor[2] = 30;					
		break;
	case 89: 
		agentData->rgbColor[0] = 30;
		agentData->rgbColor[1] = 240;
		agentData->rgbColor[2] = 30;					
		break;
	
	case 90: 
		agentData->rgbColor[0] = 60;
		agentData->rgbColor[1] = 60;
		agentData->rgbColor[2] = 0;					
		break;
	case 91: 
		agentData->rgbColor[0] = 90;
		agentData->rgbColor[1] = 90;
		agentData->rgbColor[2] = 0;					
		break;
	case 92: 
		agentData->rgbColor[0] = 120;
		agentData->rgbColor[1] = 120;
		agentData->rgbColor[2] = 0;					
		break;
	case 93: 
		agentData->rgbColor[0] = 150;
		agentData->rgbColor[1] = 150;
		agentData->rgbColor[2] = 0;					
		break;
	case 94: 
		agentData->rgbColor[0] = 180;
		agentData->rgbColor[1] = 180;
		agentData->rgbColor[2] = 0;					
		break;
	case 95: 
		agentData->rgbColor[0] = 210;
		agentData->rgbColor[1] = 210;
		agentData->rgbColor[2] = 0;					
		break;
	case 96: 
		agentData->rgbColor[0] = 240;
		agentData->rgbColor[1] = 240;
		agentData->rgbColor[2] = 0;					
		break;
	
	case 97: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 60;
		agentData->rgbColor[2] = 60;					
		break;
	case 98: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 90;
		agentData->rgbColor[2] = 90;					
		break;
	case 99: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 120;
		agentData->rgbColor[2] = 120;					
		break;
	case 100: 
		agentData->rgbColor[0] = 0;
		agentData->rgbColor[1] = 150;
		agentData->rgbColor[2] = 150;					
		break;
	
	}
}
