#ifndef NORMALSOCKET_H_
#define NORMALSOCKET_H_

#include "socket.h"

/*normal socket. so tem uma inicializacao diferente, opcionalmente voce pode setar ja
 * um socket atraves da fun?ao setsocket e assim nao precisa chamar o metodo 
 * initialize() */

namespace net
{

class NormalSocket : public net::Socket {

	public:
	
		void initialize(int port, char* ip);
		void setSocket(int s) { sock = s; };

};


}

#endif /*NORMALSOCKET_H_*/
