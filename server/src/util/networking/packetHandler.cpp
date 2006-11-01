
#include "packetHandler.h"
#include "client.h"
#include "packet.h"
#include "../errors/exceptions.h"
#include <map>
#include <iostream>

using namespace net;
using namespace errors;

bool PacketHandler::initialize(){
	return true;
}

bool PacketHandler::handlePackets(Server& server){

	std::map <int, Client*>::const_iterator iter;
	bool res = false;

	for(iter = server.getFirstClient(); iter != server.getLastClient(); iter++){
		
		if(!iter->second->getPacketCount()) {
			continue;
		}
		
		res = true;

		Client* who = iter->second;
		Packet& message = who->getFirstPacket();
		int ID = message.getID();

		try {
			if(ID == 1) {
				std::cout << "ID 1 recebida" << std::endl;
				std::cout << "msg: " << message.getString(message.getLen()-2) << std::endl;
			} else {
				std::cerr << "Unknown message " << (int) ID;
				std::cerr << " from client #" << who->getId();
				std::cerr << ", len: " << message.getLen() << std::endl;
			}
		} catch(PacketException & E) {
			std::cerr << "Exception in message " << static_cast <int> (ID);
			std::cerr << " from client #" << who->getId();
			std::cerr << ": " << E.getText() << std::endl;
			//TODO disconect
			return res;
		} catch(...) {
			std::cerr << "Unknown Exception in message " << static_cast <int> (ID);
			std::cerr << " from client #" << who->getId();
			std::cerr << "!" << std::endl;
			//TODO Disconect 
			return res;
		}
		iter->second->popPacket();
	}
	return res;
	
}

