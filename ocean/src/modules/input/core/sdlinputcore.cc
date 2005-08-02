
#include "sdlinputcore.h"
#include "../event.h"
#include <SDL/SDL.h>

void sdlInputCore::doInput(){
	
	SDL_Event event;
	
	Uint8 *keys = SDL_GetKeyState(NULL);
	if ( keys[SDLK_UP] ) { sendEvent(E_UP); }
	if ( keys[SDLK_DOWN] ) { sendEvent(E_DOWN); }
	if ( keys[SDLK_LEFT] ) { sendEvent(E_LEFT); }
	if ( keys[SDLK_RIGHT] ) { sendEvent(E_RIGHT); }
	
	while(SDL_PollEvent( &event )){
		switch( event.type ){
			case SDL_QUIT:
			    sendEvent(E_APPCLOSE);
			    break;
			
		}	
	}
	
}
