
#include "socket.h"
#include "../../errors/exceptions.h"
#include <fcntl.h>

using namespace net;

void Socket::closeSocket(){
	close(sock);	
}

void Socket::sendPacket(Packet& data){
	
	data.seal();
	int len = data.getLen();
	char* packet = new char[len];
	for(int i = 0; i < len; i++)
		packet[i] = data.getBYTE();
	if(send(getSocket(), packet, len, 0) != len) {
      // TODO: adicionar em uma queue ou kica-lo ?
		// close(sock);
	}
	delete [] packet;
}

void Socket::makeNonBlocking(){

	fcntl(sock, F_SETFL, O_NONBLOCK);
	
}
