#ifndef CLIENT_H_
#define CLIENT_H_

#include "packet.h"
#include "sockets/normalsocket.h"
#include <vector>
#include <queue>

namespace net{

class Client{
	
	public:
	
		Client(){};
		Client(int sock, unsigned int ID) : id(ID) { clientSocket.setSocket(sock);};
		
		int getSocket(){ return clientSocket.getSocket(); };
		unsigned int getId(){return id; };
		Packet& getFirstPacket();
		int getPacketCount(){return packets.size(); };
		
		void addChunk(unsigned char* Chunk, size_t size);
		
		void popPacket();
		void send(Packet& data);
	
	private:
	
		net::NormalSocket clientSocket;
		unsigned int id;
		std::vector <unsigned char> buffer;
		std::queue <Packet> packets;
	
};
	
	
}

#endif /*CLIENT_H_*/
