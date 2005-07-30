//#include "sound/soundsystem.h"
//#include "sound/sound.h"
#include "engine.h"
#include "util/drawfunctions.h"
#include "modules/input/core/sdlinputcore.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <iostream>

engine::engine(){ 
	done = false;
	pressioned = false;
	firstx = firsty =  0;
	secondx = secondy = 0;
}

engine::~engine(){
}

void engine::drawbackground(){
	video->lock();
		drawgrid(SDL_GetVideoSurface(), video->getWidth(), video->getHeight(), 10, 255, 255,255);
 	video->unlock();
}

void engine::clear(){
	video->lock();
		SDL_FillRect(SDL_GetVideoSurface(),NULL,0x000000);
	video->unlock();
}
	
bool engine::initialize(){

	std::cout << "Inicializando engine..." << std::endl;
	video = new videosystem();
	if (!video->initialize(videosystem::HWSURFACE | videosystem::RES_800x600 | videosystem::BPP_8))
		return false;
	video->setWindowTitle("Ocean");
	
//	som = new soundsystem();
//	som->initialize(22050, AUDIO_S16, 2, 4096);
//	som->play("Hydrate-Kenny_Beltrey.ogg");

    manager.addEntity("vikings", 450, 50);

	std::cout << "Engine inicializada com sucesso!" << std::endl;
	return true;
	
}

void engine::shutdown(){
	if (video)
		delete video;
}

void engine::draw(){
	video->lock();
    manager.draw();
	video->unlock();
}

void engine::update(){
}

void engine::main(){

	while(!done){
		draw();
		InputCore::getInstance().doInput();
	}
	
}

void engine::handleEvent(const event &e){

	switch (e.type) {
      case E_APPCLOSE:
        done = true;
        break;
    }
	
	
}

int main()
{
	engine eng;
	eng.initialize();
	eng.main();
	eng.shutdown();
	return 0;
}
