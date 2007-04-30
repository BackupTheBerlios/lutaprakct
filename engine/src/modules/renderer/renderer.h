#ifndef RENDERER_H_
#define RENDERER_H_

#include "../core/task.h"
#include "video/videosystem.h"
#include "../mesh/terrain/terrain.h"
#include "camera/camera.h"
#include "frustum/frustum.h"
#include "../events/eventhandler.h"
#include "../../util/patterns/singleton.h"
#include "../../util/structures/octree.h"
#include "../mesh/skybox/skybox.h"
#include "../mesh/mesh.h"

class Renderer : public Task, public EventHandler {
	
public:

	Renderer(): video(NULL), geometry(NULL){ };
	
	bool start(void* data);
	void stop(void* data);
	void update(void* data);
	
	void handleEvent(const event &e);
	
	AUTO_SIZE;
	
private:

	void setup2dRendering();

	void drawOctree(Octree* node);

	Terrain terrain;
	Octree* geometry;
	VideoSystem* video;
	Skybox sky;
	Frustum frustum;
	
	std::list<Mesh*> meshes;
	
	int screenShotNumber;
	
};

typedef Singleton<Renderer> RENDERER;

#endif /*RENDERER_H_*/
