#ifndef RENDERER_H_
#define RENDERER_H_

#include "../core/task.h"
#include "video/videosystem.h"
#include "../mesh/terrain/terrain.h"
#include "camera/camera.h"

class Renderer : public Task{
	
public:

	Renderer(){ video = NULL; }
	
	bool start(void* data);
	void stop(void* data);
	void update(void* data);
	
	void setup2dRendering();
	
	AUTO_SIZE;
	
private:

	Terrain terrain;
	videoSystem *video;
	
};

#endif /*RENDERER_H_*/
