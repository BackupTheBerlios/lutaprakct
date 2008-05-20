#ifndef _SDLINPUTCORE_H_
#define _SDLINPUTCORE_H_

#include "../eventhandler.h"
#include "../../util/Singleton.h"
#include <list>

/**outro singleton do sistema de eventos. esse eh o responsavel por pegar o input do SDL
 * com a funcao update() e enviar pro eventdispatcher que sua vez envia para todos os outros
 * handlers.
 * Na pratica basta  chamar update(); no mainloop da engine
 * OBS.: o input precisa saber o tamanho da janela pra calcular quanto o mouse se moveu.
 */

class SdlInputCore : public EventHandler{
	
public:

	SdlInputCore(){};
	virtual ~SdlInputCore(){};
	
	void handleEvent(const event &e){};
	
	bool initialize(int x, int y);
	bool update();
	void stop();
	
	void setWindowSize(unsigned int x, unsigned int y);
	void setMouseVelocity(float v);
	
	float getMouseVelocity(){ return mouseVelocity; }
	
private:

	unsigned int winHeight, winWidth;
	unsigned int widthMiddle, heightMiddle;
	float mouseVelocity;
	
	
};

typedef Singleton<SdlInputCore> INPUT;

#endif //_SDLINPUTCORE_H_
