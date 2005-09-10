
#include "videofactory.h"

#include "../../../modules/video/videosystem.h"
#include "../../../modules/video/sdlvideo/sdlvideo.h"

product* videoFactory::create(std::string args){
	
	   if (args == "sdlvideo"){
	       videoSystem *aux;
	       aux = new sdlVideo();
	       return (product*) aux;
	   }
}

