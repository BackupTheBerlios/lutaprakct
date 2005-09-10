#ifndef _VIDEOFACTORY_H_
#define _VIDEOFACTORY_H_

#include "../abstractfactory.h"
#include "../singleton.h"
#include <string>

/*factory do video. de acordo com a string que recebe ela retorna a instancia
 * apropriada de video.
 */

class videoFactory : public abstractFactory {
	
public:
	videoFactory(){};
	~videoFactory(){};
    product* create(std:: string args =0);
	
	
};

typedef singleton<videoFactory> VideoFactory;

#endif //_VIDEOFACTORY_H_
