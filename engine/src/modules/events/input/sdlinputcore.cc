
#include "sdlinputcore.h"
#include "../event.h"
#include <SDL/SDL.h>

void SdlInputCore::stop(){
}

//TODO alterar o lance do 800x600
bool SdlInputCore::start(){
	informWindowSize(800, 600);
	setMouseVelocity(10.0);
	return true;	
}

void SdlInputCore::update(){
	
	SDL_Event event_sdl;
	
	while(SDL_PollEvent( &event_sdl )){
		switch( event_sdl.type ){
			case SDL_QUIT:
			    sendEvent(E_APPCLOSE);
		}		
	}
	
	/*keyboard input */
	Uint8 *keystate = SDL_GetKeyState(NULL);
    if ( keystate[SDLK_UP] ) sendEvent(E_KEY_UP);
    if ( keystate[SDLK_DOWN] ) sendEvent(E_KEY_DOWN);
    if ( keystate[SDLK_LEFT] ) sendEvent(E_KEY_LEFT);
    if ( keystate[SDLK_RIGHT] ) sendEvent(E_KEY_RIGHT);
    
    /* mouse input */
	int x, y;

	int widthMiddle = winwidth / 2;
	int heightMiddle = winheight / 2;

	SDL_GetMouseState(&x, &y);
	
	if (x != widthMiddle){
		sendEvent(E_MOUSE_ROTATE_X, (x-widthMiddle)*mouseVelocity);
//		c->rotate((x - widthMiddle) * velMouse, vec3(0.0, 1.0, 0.0));
	}if (y != heightMiddle){
		sendEvent(E_MOUSE_ROTATE_Y, (y-heightMiddle)*mouseVelocity);
	//	c->rotate((y - heightMiddle) * velMouse, vec3(1.0, 0.0, 0.0));
	}
	
	SDL_WarpMouse(widthMiddle, heightMiddle);
	
}

void SdlInputCore::informWindowSize(unsigned int x, unsigned int y){

	winwidth = x;
	winheight = y;
	
}

void SdlInputCore::setMouseVelocity(float v){
	mouseVelocity =v;
}