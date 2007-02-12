
#include "timer.h"
#include "SDL/SDL.h"

#include <iostream>

Timer::Timer(){
		
	if (!SDL_WasInit(SDL_INIT_TIMER))
		SDL_InitSubSystem(SDL_INIT_TIMER);
}

bool Timer::start(void* data ){
	
	fps = 60;
	elapsedTime = 0;
	currentTime = 0;
	lastTime = 0;
	return true;
}

void Timer::update(void* data ){
	
	//calculo do tempo que passou desse frame pro anterior
	lastTime = currentTime;
	currentTime = SDL_GetTicks();
	elapsedTime = ((float)(currentTime-lastTime))/1000.0f;
	
	//calculo do fps. sempre que passarem 100 frames divide 100 pelo tempo dos 100 (em media)
	static int ticks;
	if(ticks >= 1000) {
		fps = ticks / (float)(elapsedTime*1000.0);
		std::cout << "fps " << fps << std::endl;
		ticks = 0;
	}
	ticks++;
	
//	std::cout << "fps " << fps << " current time " << currentTime << " lastTime " << lastTime <<" elapsed time " << elapsedTime << std::endl;
}
