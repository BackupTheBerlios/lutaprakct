#ifndef SERVER_CPP_
#define SERVER_CPP_

#include "server.h"

using namespace net;

std::map <int, Client*>::const_iterator Server::getFirstClient(){

	return clients.begin();
}

std::map <int, Client*>::const_iterator Server::getLastClient(){

	return clients.end();
}

void Server::initialize(int port){

	serverSocket.initialize(port, NULL);
	lastClientId = 1;
	
}

void Server::checkConnections(){

	int newClient = serverSocket.checkConnections();
	
	if (newClient >= -1){
		clients[newClient] = new Client(newClient, lastClientId++);
	}
	
}

/* essa funcao percorre todos os clients e verifica se algum deles precisa de um recv()
 * se precisar, ele pega os packets e coloca na lista e packets do client.
 */

bool Server::checkPackets(){

	fd_set error, packets;
	std::map <int, Client*>::const_iterator iter;
	timeval timeout;
	bool res = false;

	timeout.tv_sec    = 0;
	timeout.tv_usec   = 0;

	FD_ZERO(&error);
	FD_ZERO(&packets);

	int i = 0;
	for(iter = clients.begin(); iter != clients.end(); iter++){
		i++;
		int sock = iter->second->getSocket();
		Client* client = iter->second;

		FD_SET(sock, &error);
		FD_SET(sock, &packets);
		if(select(static_cast <unsigned> (sock + 1), &packets, 0, &error, &timeout) <= 0)
			continue;
		if(FD_ISSET(sock, &error)) {
			//TODO disconect o client
			continue;
		}else if(FD_ISSET(sock, &packets)) {
			unsigned char Chunk[50];

			int count = recv(sock, reinterpret_cast <char *> (Chunk), sizeof(Chunk), 0);
			if(count > 0) {
				res = true;
				client->addChunk(Chunk, count);
			}else{
				//TODO disconect o client
				continue;
			}
		}
	}

	return res;
	
}

#endif /*SERVER_CPP_*/
