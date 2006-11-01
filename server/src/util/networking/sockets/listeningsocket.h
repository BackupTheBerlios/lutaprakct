#ifndef LISTENINGSOCKET_H_
#define LISTENINGSOCKET_H_

#include "socket.h"

namespace net
{

/*socket do server. que usa listen, bind e accept no initialize(). o checkConections deve
 * ser chamado todo frame para ver se tem conexoes novas. se ele fizer um accept ele retorna
 * o socket conectado ao server */

class ListeningSocket : public net::Socket {

	public:
		void initialize(int port, char* ip);

		int checkConnections();

};


}

#endif /*LISTENINGSOCKET_H_*/
