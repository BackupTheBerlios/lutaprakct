#ifndef RENDERER_H_
#define RENDERER_H_

#include "../core/task.h"
#include "video/videosystem.h"

class Renderer : public Task{
	
public:

	bool start();
	void stop();
	void update();
	
	AUTO_SIZE;
	
private:

	videoSystem *video;
	
};

#endif /*RENDERER_H_*/
