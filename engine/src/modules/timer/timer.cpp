
#include "timer.h"
#include "SDL/SDL.h"

timer::timer(){
	fps = 60;
	spf = 1/60;
	
	if (SDL_WasInit(SDL_INIT_TIMER))
		SDL_InitSubSystem(SDL_INIT_TIMER);
}

void timer::update(){
	
	static int startTime, endTime, ticks;
	
	if(ticks >= 100) {
		endTime = startTime;
		startTime = SDL_GetTicks();
		fps = (ticks / (float)(startTime - endTime)) * 1000.0;
		spf = 1 / fps;
		ticks = 0;
	}
	ticks++;
}