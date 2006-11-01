#ifndef SERVER_H_
#define SERVER_H_

#include "sockets/listeningsocket.h"
#include "client.h"
#include <map>

namespace net {

//TODO deveria ser um singleton?

class Server{
	
	public:
	
		void initialize(int port);
		void shutdown();
		
		void checkConnections();
		bool checkPackets();
		
		std::map <int, Client*>::const_iterator getFirstClient();
		std::map <int, Client*>::const_iterator getLastClient();
		
	private:
	
		unsigned int lastClientId;
		
		ListeningSocket serverSocket;
		std::map <int, Client*> clients;
};
	
}

#endif /*SERVER_H_*/
