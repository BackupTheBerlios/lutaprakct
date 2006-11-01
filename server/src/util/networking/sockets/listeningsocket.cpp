
#include "listeningsocket.h"
#include "../../errors/exceptions.h"

using namespace net;

void ListeningSocket::initialize(int port, char* ip){

	//TODO passar o tipo tcp ou udp por parametro
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1) 
		throw errors::NetworkException("Couldn't create listen socket");
	
	makeNonBlocking();
	addr.sin_family = AF_INET; 
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(addr.sin_zero), '\0', 8); // zera a struct

    if (bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) 
		throw errors::NetworkException("Couldn't bind listen socket");
    
    listen(sock, 20);
	
}

int ListeningSocket::checkConnections(){

	fd_set connections;
	timeval timeout; //timeout usado na funcao select

	FD_ZERO(&connections);
	FD_SET(sock, &connections);
	timeout.tv_sec    = 0;
	timeout.tv_usec   = 0;
	
	int newsocket;
	if(select( sock+1, &connections, 0, 0, &timeout) > 0){
		newsocket = accept(sock, 0, 0);
		if(newsocket == -1) {
			close(newsocket);
		} else {
			makeNonBlocking();
		}
	}
	return newsocket;
	
}


