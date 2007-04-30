#ifndef OBJRENDERER_H_
#define OBJRENDERER_H_

#include "meshRenderer.h"
#include "../meshData.h"

class ObjRenderer : public MeshRenderer{
	
public:
	
	ObjRenderer(){};
	virtual ~ObjRenderer(){};
	
	void draw(MeshData* data);
	void draw(MeshData* data, int frame){};
	void draw(MeshData* data, float elapsedTime, int startFrame, int lastFrame){};
	
};

#endif /*OBJRENDERER_H_*/
