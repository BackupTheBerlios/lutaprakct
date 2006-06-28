#ifndef RENDERER_H_
#define RENDERER_H_

#include "../core/task.h"
#include "video/videosystem.h"
#include "../mesh/terrain/terrain.h"
#include "camera/camera.h"

class Renderer : public Task{
	
public:

	bool start(void* data);
	void stop(void* data);
	void update(void* data);
	
	AUTO_SIZE;
	
private:

	Terrain terrain;
	videoSystem *video;
	
};

#endif /*RENDERER_H_*/
