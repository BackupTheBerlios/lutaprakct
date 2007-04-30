
#include "sdlinputcore.h"
#include "../event.h"
#include <SDL/SDL.h>
#include "../../renderer/camera/camera.h"
#include "../../timer/timer.h"
#include <iostream>
#include "../../../../libs/tinyxml/tinyxml.h"

int r, d, l, u;

void SdlInputCore::stop(void* data){
}

//TODO alterar o lance do 800x600
bool SdlInputCore::start(void* data){
	r = d = l = u = 0;
	TiXmlDocument configdoc("config.xml");
	if (!configdoc.LoadFile()){
		std::cout << "(SdlInput)ERRO: Arquivo de configuracao config.xml nao encontrado." << std::endl;
		configdoc.Clear();
		return false;
	}

	TiXmlElement* enginecfg = configdoc.FirstChildElement("engine");
	TiXmlElement* elem = enginecfg->FirstChildElement("opengl");
	elem = elem->FirstChildElement("viewport");
	int height = atoi(elem->Attribute("height"));
	int width = atoi(elem->Attribute("width"));
	setWindowSize(width, height);

	elem = configdoc.FirstChildElement("engine");
	elem = elem->FirstChildElement("events");
	if (elem){
		TiXmlElement* event = elem->FirstChildElement("event");
		while(event){
			std::string eventType = event->Attribute("type");
			automaticEvents.push_front( eventType );
			if (eventType == "MOUSE"){
				eventParams.push_front( atoi(event->Attribute("param1")) );
				eventParams.push_front( atoi(event->Attribute("param2")) );
			}
			event = event->NextSiblingElement("event");	
		}
	}
	setMouseVelocity(10.0);
	nextEvent = 5000;
	SDL_WarpMouse(widthMiddle, heightMiddle);
	
	configdoc.Clear();
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
      
	int x, y;

	SDL_GetMouseState(&x, &y);
	CAMERA::getInstance().rotateByMouse(x, y, widthMiddle, heightMiddle);

	SDL_WarpMouse(widthMiddle, heightMiddle);

	emulateAditionalEvents();
	
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

void SdlInputCore::emulateAditionalEvents(){
	
	if (!automaticEvents.empty()){
	
		std::string s = automaticEvents.front();
		
		if (s == "UP")
			sendEvent(E_KEY_W);
		else if ( s == "DOWN")
			sendEvent(E_KEY_S);
		else if ( s == "ZOOM_IN")
			sendEvent(E_KEY_UP);
		else if ( s == "ZOOM_OUT")
			sendEvent(E_KEY_DOWN);
		else if ( s == "LEFT")
			sendEvent(E_KEY_LEFT);
		else if ( s == "RIGHT")
			sendEvent(E_KEY_RIGHT);
		else if ( s == "SCREENSHOT")
			sendEvent(E_KEY_F1);
		else if ( s == "MOUSE"){
			int ymod = eventParams.front();
			eventParams.pop_front();
			int xmod = eventParams.front();
			eventParams.pop_front();
			CAMERA::getInstance().rotateByMouse(widthMiddle+xmod, heightMiddle+ymod, widthMiddle, heightMiddle);
		}
			
		automaticEvents.pop_front();
	}

}
