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
 * OBS.: o input precisa saber o tamanho da janela pra calcular quanto o mouse se moveu.
 */

class sdlInputCore : public eventHandler{
	
public:

	sdlInputCore(){};
	~sdlInputCore(){};
	
	void handleEvent(const event &e){};
	
	void doInput();
	
	void informWindowSize(int x, int y);
	void setMouseVelocity(float v);
	
private:

	int winheight, winwidth;
	float mouseVelocity;
	
};

typedef singleton<sdlInputCore> InputCore;

#endif //_SDLINPUTCORE_H_
