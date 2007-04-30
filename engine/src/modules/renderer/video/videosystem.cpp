
#include "videosystem.h"
#include "sdlvideo/sdlvideo.h"

VideoSystem* initializeVideo(int videoType){
	
	if (videoType == VideoSystem::VIDEO_SDL){
		VideoSystem *aux;
		aux = new SdlVideo();
		return aux;
	}
	
	return NULL;
}
