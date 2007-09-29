
#include "Timer.h"
#include "SDL/SDL.h"

#include <iostream>

Timer::Timer(){
		
	if (!SDL_WasInit(SDL_INIT_TIMER))
		SDL_InitSubSystem(SDL_INIT_TIMER);
}

bool Timer::initialize(){
	
	fps = 60;
	elapsedTime = 0;
	currentTime = 0;
	lastTime = 0;
	return true;
	
}

void Timer::update( ){
	
	//calculo do tempo que passou desse frame pro anterior
	lastTime = currentTime;
	currentTime = SDL_GetTicks();
	elapsedTime = ((float)(currentTime-lastTime))/1000.0f;
	
	//calculo do fps. sempre que passarem 100 frames divide 100 pelo tempo dos 100 (em media)
	static int ticks;
	if(ticks >= 1000) {
		fps = ticks / (float)(elapsedTime*1000.0);
		ticks = 0;
	}
	ticks++;
	
}
