#include <iostream>
#include <ctime>

#include "util/files/files.h"
#include "util/files/cfgfile.h"
#include "util/threads/threads.h"
#include "util/networking/server.h"
#include "util/networking/packetHandler.h"

#include "util/lua/luaVM.h"

#include "agents/arch/subsumption/sample/agentTest.h"
#include "agents/ambient/sample/testAmbient.h"

int main(int argc, char **argv){
	
	net::Server server;
	net::PacketHandler netHandler;
	files::CfgFile CFG;
	
	lua::LuaVM lua;
	
	std::cout << "Server Version 0.1" << std::endl;
#ifdef WORDS_BIGENDIAN
	std::cout << "Using Big Endian" << std::endl;
#endif
	std::cout << std::endl;
	
	try {
		srand(static_cast <unsigned> (time(0)) );
		unsigned int startTime = threads::Ticks();
		//CFG.open("server.cfg");
		server.initialize(5000);
		lua.initialize();
		lua.loadScripts("");
		std::cout << "Initialization done, " << threads::Ticks() - startTime << " msec." << std::endl;
	} catch(errors::Exception& E) {
		std::cerr << "Exception during startup! " << E.getText() << std::endl;
		return 0;
	}
	
/*	double x, y, z;
	x = 2;
	y = 3;
	z = 0;
	lua.callFunction("add", "dd>d", x, y, &z );
	std::cout << "z: " << z << std::endl;*/
	
	AgentTest* agent1 = new AgentTest();
	agent1->initialize("");
	agent1->setPositionX(10);
	agent1->setPositionY(10);
	agent1->start();
	AMBIENT::getInstance().addAgent(agent1);
	
	AgentTest* agent2 = new AgentTest();
	agent2->initialize("");
	agent2->setPositionX(9);
	agent2->setPositionY(10);
	agent2->start();
	AMBIENT::getInstance().addAgent(agent2);
	
	while(1){
		try {
			server.checkConnections();
			server.checkPackets();
			agent1->run();
			agent2->run();
			if(!netHandler.handlePackets(server)) {
				threads::Delay(25);
			}
		} catch(errors::Exception& E) {
			std::cerr << E.getText() << std::endl;
		}
	}

	//shutdown
	try {
		std::cout << "Power down." << std::endl;
	} catch(errors::Exception& E) {
		std::cerr << "Exception during shutdown! " << E.getText() << std::endl;
		return EXIT_FAILURE;
	}
	return 1;	
}
