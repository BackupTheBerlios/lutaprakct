
#include "normalsocket.h"

#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

using namespace net;

void NormalSocket::initialize(int port, char* ip){

	//hostent *he;
	//TODO passar o tipo tcp ou udp por parametro
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1) 
		throw errors::NetworkException("Couldn't create normal socket");
	
	makeNonBlocking();
	addr.sin_family = AF_INET; 
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
    memset(&(addr.sin_zero), '\0', 8); // zera a struct
    
	if (connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
		throw errors::NetworkException("Couldn't connect to host");
    }
	
}

