
#include "sdlinputcore.h"
#include "../event.h"
#include <SDL/SDL.h>

void sdlInputCore::doInput(){
	
	SDL_Event event;
	
	while(SDL_PollEvent( &event )){
	
	
		switch( event.type ){
			
			case SDL_QUIT:
			    sendEvent(E_APPCLOSE);
			
		}	
		
		
	}
	
}
