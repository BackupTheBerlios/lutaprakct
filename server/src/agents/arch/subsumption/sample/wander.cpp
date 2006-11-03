#include "wander.h"
#include "agentTest.h"
#include "testAgentData.h"
#include <iostream>

void WanderLayer::run(SubsumptionAgentData* data, void* auxiliarData){
	
	TestAgentData* agentData = static_cast<TestAgentData*>(auxiliarData);
	std::cout << "evitanto obstaculos " << std::endl;
	
	if (agentData->caminhos[0]){
		agentData->x = agentData->x-10;
		agentData->y = agentData->y-10;
		agentData->posx = agentData->posx-1;
		agentData->posy = agentData->posy-1;
	}else if (agentData->caminhos[1]){
		agentData->y = agentData->y-10;
		agentData->posy = agentData->posy-1;
	}else if (agentData->caminhos[2]){
		agentData->x = agentData->x+10;
		agentData->y = agentData->y-10;
		agentData->posx = agentData->posx+1;
		agentData->posy = agentData->posy-1;
	}else if (agentData->caminhos[3]){
		agentData->x = agentData->x+10;
		agentData->posx = agentData->posx+1;
	}else if (agentData->caminhos[4]){
		agentData->x = agentData->x+10;
		agentData->y = agentData->y+10;
		agentData->posx = agentData->posx+1;
		agentData->posy = agentData->posy+1;
	}else if (agentData->caminhos[5]){
		agentData->y = agentData->y+10;
		agentData->posy = agentData->posy+1;
	}else if (agentData->caminhos[6]){
		agentData->x = agentData->x-10;
		agentData->y = agentData->y+10;
		agentData->posx = agentData->posx-1;
		agentData->posy = agentData->posy+1;
	}else if (agentData->caminhos[7]){
		agentData->x = agentData->x-10;
		agentData->posx = agentData->posx-1;
	}
	
	for (unsigned int i = 0; i<8; i++)
		agentData->caminhos[i] = false;
	
}
