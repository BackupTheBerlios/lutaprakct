#ifndef PACKETHANDLER_H_
#define PACKETHANDLER_H_

#include "server.h"

namespace net{

class PacketHandler{
	
	public:
		
		PacketHandler(){};
		~PacketHandler(){};
	
		bool initialize();
	
		bool handlePackets(Server& server);
	
};
	
	
}

#endif /*PACKETHANDLER_H_*/
