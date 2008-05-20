#ifndef ENGINE_H_
#define ENGINE_H_

#include "events/event.h"
#include <list>

class Engine{
	
	public:
	
		Engine();
		~Engine();
		
		bool initialize();
		
		void mainLoop();
		
		bool isRunning();
		void stop();
		void shutdown();
		
	private:
	
		bool running;
		
		std::list<event> emulatedEvents; //eventos que sao disparados logo que a engine inicia
}; 

#endif /*ENGINE_H_*/
