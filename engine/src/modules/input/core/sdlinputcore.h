#ifndef _SDLINPUTCORE_H_
#define _SDLINPUTCORE_H_

#include "../eventhandler.h"
#include "../../../util/patterns/singleton.h"

/**outro singleton do sistema de eventos. esse eh o responsavel por pegar o input do SDL
 * com a funcao doInput() e enviar pro eventdispatcher que sua vez envia para todos os outros
 * handlers.
 * Na pratica basta  chamar doInput(); no mainloop da engine
 * TODO existe a necessidade de criar factory pra isso para suportar outras implementacoes
 * que nao usem SDL?  mas caso necessite basta refazer o doInput()
 */

class sdlInputCore : public eventHandler{
	
public:

	sdlInputCore(){};
	~sdlInputCore(){};
	
	void handleEvent(const event &e){};
	
	void doInput();
	
};

typedef singleton<sdlInputCore> InputCore;

#endif //_SDLINPUTCORE_H_
