
#include "sdlinputcore.h"
#include "../event.h"
#include <SDL/SDL.h>
#include <iostream>

void SdlInputCore::stop(){
}

//TODO alterar o lance do 800x600
bool SdlInputCore::initialize(int x, int y){

	int height = y;
	int width = x;
	setWindowSize(width, height);

	setMouseVelocity(10.0);
	SDL_WarpMouse(widthMiddle, heightMiddle);
	
	return true;	
}

bool SdlInputCore::update(){
	
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
    if ( keystate[SDLK_ESCAPE] ) return false;
    if ( keystate[SDLK_F1] ) sendEvent(E_KEY_F1);
    if ( keystate[SDLK_w] ) sendEvent(E_KEY_W);
    if ( keystate[SDLK_s] ) sendEvent(E_KEY_S);
      
	int x, y;

	SDL_GetMouseState(&x, &y);
	sendEvent(E_MOUSE_POSITION, x, y);

	SDL_WarpMouse(widthMiddle, heightMiddle);
	
	return true;
}

void SdlInputCore::setWindowSize(unsigned int x, unsigned int y){

	winWidth = x;
	winHeight = y;

	widthMiddle = winWidth / 2;
	heightMiddle = winHeight / 2;
	
}

void SdlInputCore::setMouseVelocity(float v){
	mouseVelocity =v;
}
