
#include <SDL/SDL.h>

#include "engine.h"

#include "util/logger/logger.h"
#include "util/profiler/profiler.h"
#include "util/profiler/profilerLogger.h"

#include "modules/renderer/renderer.h"
#include "modules/core/kernel.h"
//#include "modules/timer/timer.h"

void Engine::run(){
	
	//inicializa a seed para numeros random
	srand((unsigned)time(NULL));
	
	if(!LOGGER::getInstance().initialize())return;

	LOGGER::getInstance().write("start.log", "Inicializando engine");

	//parse the 'settings.eng' file
	//SETTINGS::getInstance().parseFile("settings.esf");

	LOGGER::getInstance().write("start.log", "Inicializando renderer");	
	rendererTask = new Renderer();
	rendererTask->priority=10000;
	KERNEL::getInstance().addTask( (MemoryManagedPointer<Task>(rendererTask)) );

	LOGGER::getInstance().write("start.log", "Inicializando input");	
	inputTask = new SdlInputCore();
	inputTask->priority=20;
	KERNEL::getInstance().addTask(MemoryManagedPointer<Task>(inputTask));

/*	globalTimer=new Timer();
	globalTimer->priority=10;
	KERNEL::getInstance().addTask(MemoryManagedPointer<Task>(globalTimer));*/

	LOGGER::getInstance().write("start.log", "Inicializando profiler");
	//set up the profiler with an output handler
	ProfileLogHandler profileLogHandler;
	ProfileSample::outputHandler=&profileLogHandler;

	//main game loop
	KERNEL::getInstance().execute();
	
}

int main(int argc, char *argv[])
{
	Engine eng;
	eng.run();
	return 0;
}
