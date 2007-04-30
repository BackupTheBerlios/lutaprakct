#ifndef _SDLINPUTCORE_H_
#define _SDLINPUTCORE_H_

#include "../eventhandler.h"
//#include "../../../util/patterns/singleton.h"
#include "../../core/task.h"
#include <list>

/**outro singleton do sistema de eventos. esse eh o responsavel por pegar o input do SDL
 * com a funcao update() e enviar pro eventdispatcher que sua vez envia para todos os outros
 * handlers.
 * Na pratica basta  chamar update(); no mainloop da engine
 * TODO existe a necessidade de criar factory pra isso para suportar outras implementacoes
 * que nao usem SDL?  mas caso necessite basta refazer o update()
 * OBS.: o input precisa saber o tamanho da janela pra calcular quanto o mouse se moveu.
 */

class SdlInputCore : public EventHandler , public Task{
	
public:

	SdlInputCore(){};
	virtual ~SdlInputCore(){};
	
	void handleEvent(const event &e){};
	
	bool start(void* data);
	void update(void* data);
	void stop(void* data);
	
	void setWindowSize(unsigned int x, unsigned int y);
	void setMouseVelocity(float v);
	
	float getMouseVelocity(){ return mouseVelocity; }
	
	AUTO_SIZE;
private:

	void emulateAditionalEvents();
	long int nextEvent;

	unsigned int winHeight, winWidth;
	unsigned int widthMiddle, heightMiddle;
	float mouseVelocity;
	
	std::list<std::string> automaticEvents;
	std::list<int> eventParams;
	
};

//typedef singleton<SdlInputCore> INPUT;

#endif //_SDLINPUTCORE_H_
