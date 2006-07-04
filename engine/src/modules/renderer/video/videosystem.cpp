
#include "videosystem.h"
#include "sdlvideo/sdlvideo.h"

videoSystem* initializeVideo(int videoType){
	
	if (videoType == videoSystem::VIDEO_SDL){
		videoSystem *aux;
		aux = new sdlVideo();
		return aux;
	}
	
	return NULL;
}
