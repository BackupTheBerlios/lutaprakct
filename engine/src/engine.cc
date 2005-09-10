
#include "engine.h"
#include "modules/input/core/sdlinputcore.h"
#include <iostream>





engine::engine(){ 
	done = false;
}

engine::~engine(){
}

	
bool engine::initialize(){

	std::cout << "Inicianlizando Engine..." << std::endl;

	video = (videoSystem*)VideoFactory::getInstance().create("sdlvideo");
	if (!video->initialize(videoSystem::HWSURFACE | videoSystem::DOUBLEBUF | videoSystem::RES_800x600 | videoSystem::BPP_8 | videoSystem::OPENGL ))
		return false;
	video->setWindowTitle("Engine");

    std::cout << "Engine inicializada com sucesso!" << std::endl;
	return true;
	
}

void engine::shutdown(){
	if (video)
		delete video;
}

void engine::draw(){
	video->lock();
	


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
