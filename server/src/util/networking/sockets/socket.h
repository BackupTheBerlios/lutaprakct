#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../packet.h"

namespace net{

	/*interface socket. vai ter dois tipos de sockets, um listeningsocket que vai usar
	 * bind(), listen() e accept() e fazer o papel do servidor e o normalsocket que vai fazer o
	 * papel do client usando conect().
	 * alguns metodos mais genericos como close, send e receive sao implementados nessa classe
	 * */

	class Socket{
		
		public:
		
			virtual void initialize(int port, char* ip) = 0;
			void sendPacket(Packet& data);
			void makeNonBlocking();
			void closeSocket();
			
			int getSocket() {return sock;}

		protected:
		
			int sock;
			sockaddr_in addr;
			
	};

}

#endif /*SOCKET_H_*/
