
#include "videofactory.h"

#include "../../../modules/renderer/video/videosystem.h"
#include "../../../modules/renderer/video/sdlvideo/sdlvideo.h"

product* videoFactory::create(std::string args){
	
	   if (args == "sdlvideo"){
	       videoSystem *aux;
	       aux = new sdlVideo();
	       return (product*) aux;
	   }
}

