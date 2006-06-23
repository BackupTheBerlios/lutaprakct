
#include "renderer.h"

#include "../../util/interfaces/product.h"
#include "../../util/patterns/factories/videofactory.h"

void Renderer::stop(){
}

bool Renderer::start(){

	video = (videoSystem*)VideoFactory::getInstance().create("sdlvideo");
	if (!video->initialize( videoSystem::RES_800x600 | videoSystem::BPP_8 | videoSystem::OPENGL ))
		return false;
	video->setWindowTitle("Engine");
    video->showCursor(false);

	return true;
	
}

void Renderer::update(){

	video->lock();
	
	/*loop em todas entidades visiveis pra desenha-las*/
	
	video->unlock();
	
}
