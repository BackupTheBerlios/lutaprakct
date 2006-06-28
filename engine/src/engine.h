
#ifndef _ENGINE_H_
#define _ENGINE_H_

//#include "modules/timer/timer.h"
#include "modules/renderer/renderer.h"
#include "modules/events/input/sdlinputcore.h"

/** classe basica de controle da engine. As instancias
    dos sub sistemas ficam nessa classe.
*/

class Engine{
 
public:
	Engine(){};
	~Engine(){};

	void run();

private:

	MemoryManagedPointer<SdlInputCore> inputTask;
//	MemoryManagedPointer<Timer> globalTimer;
	MemoryManagedPointer<Renderer> rendererTask;

};


#endif

