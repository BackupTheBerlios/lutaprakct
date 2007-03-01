
#include "sdlinputcore.h"
#include "../event.h"
#include <SDL/SDL.h>
#include "../../renderer/camera/camera.h"
#include "../../timer/timer.h"
#include <iostream>

int r, d, l, u;

void SdlInputCore::stop(void* data){
}

//TODO alterar o lance do 800x600
bool SdlInputCore::start(void* data){
	r = d = l = u = 0;
	//informWindowSize(800, 600);
	informWindowSize(144, 176);
	setMouseVelocity(10.0);
	nextEvent = 5000;
	return true;	
}

void SdlInputCore::update(void* data){
	
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
    if ( keystate[SDLK_ESCAPE] ) sendEvent(E_KEY_ESC);
    if ( keystate[SDLK_F1] ) sendEvent(E_KEY_F1);
    if ( keystate[SDLK_w] ) sendEvent(E_KEY_W);
    if ( keystate[SDLK_s] ) sendEvent(E_KEY_S);
    
	/*long int time = TIMER::getInstance().getCurrentTime();
	if 	(  (time < 10000) ){
		//std::cout << "evento emulado " << std::endl;
		if (nextEvent > (time + 1000)){
			std::cout << "R" << std::endl;
			sendEvent(E_KEY_RIGHT);
			sendEvent(E_KEY_F1);
			nextEvent = time + 1500;
		}
	}else if (time < 13000 ){
		if (nextEvent > (time + 1000)){
			std::cout << "S" << std::endl;
			sendEvent(E_KEY_S);
			sendEvent(E_KEY_F1);
			nextEvent = time + 1500;
		}
	}else if (time < 23000 ){
		if (nextEvent > (time + 1000)){
			std::cout << "L" << std::endl;
			sendEvent(E_KEY_LEFT);
			sendEvent(E_KEY_F1);
			nextEvent = time + 1500;
		}
	}else if (time < 26000 ){
		if (nextEvent > (time + 1000)){
			std::cout << "W" << std::endl;
			sendEvent(E_KEY_W);
			sendEvent(E_KEY_F1);
			nextEvent = time + 1500;
		}
	}*/
    
    if (r < 20){
    	sendEvent(E_KEY_RIGHT);
    	sendEvent(E_KEY_F1);
    	r++;
    }
    
    if (r >= 20){
    	if (d < 10){
    		sendEvent(E_KEY_S);
    		sendEvent(E_KEY_F1);
    		d++;
    	}
    }
    
    if ( (r >= 20) && ( d >= 10) ){
    	if (l < 20){
    		sendEvent(E_KEY_LEFT);
    		sendEvent(E_KEY_F1);
    		l++;
    	}    	
    }

    if ( (r >= 20) && ( d >= 10) && (l >= 20) ){
    	if (u < 10){
    		sendEvent(E_KEY_W);
    		sendEvent(E_KEY_F1);
    		u++;
    	}    	
    }
    
	int x, y;

	SDL_GetMouseState(&x, &y);
	CAMERA::getInstance().rotateByMouse(x, y, widthMiddle, heightMiddle);

	SDL_WarpMouse(widthMiddle, heightMiddle);

	//essa eh uma ideia apenas, eventos que sao disparados sempre. pode ser usado
	//para fazer videos movendo a camera automaticamente e tirando screenshots
	//TODO fazer sistema que determine quais serao os eventos
//	emulateAditionalEvents();
	
}

void SdlInputCore::informWindowSize(unsigned int x, unsigned int y){

	winwidth = x;
	winheight = y;

	widthMiddle = winwidth / 2;
	heightMiddle = winheight / 2;
	
}

void SdlInputCore::setMouseVelocity(float v){
	mouseVelocity =v;
}

void SdlInputCore::emulateAditionalEvents(){

	//so dispara eventos depois de 5 segundos
	long int time = TIMER::getInstance().getCurrentTime();
	if 	(  (time < 20000) ){
		//std::cout << "evento emulado " << std::endl;
		if (nextEvent > (time + 1000)){
			std::cout << "S" << std::endl;
			sendEvent(E_KEY_S);
			sendEvent(E_KEY_F1);
			nextEvent = time + 1500;
		}
	}else if (time < 15000 ){
		if (nextEvent > (time + 1000)){
			std::cout << "L" << std::endl;
			sendEvent(E_KEY_LEFT);
			sendEvent(E_KEY_F1);
			nextEvent = time + 1500;
		}
	}

}
