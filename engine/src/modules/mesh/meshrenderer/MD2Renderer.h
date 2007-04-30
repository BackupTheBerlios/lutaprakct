#ifndef MD2RENDERER_H_
#define MD2RENDERER_H_

#include "meshRenderer.h"

class MD2Renderer : public MeshRenderer{
	
public:
	
	MD2Renderer(){nextFrame = 0;};
	virtual ~MD2Renderer(){};
	
	void draw(MeshData* data);
	void draw(MeshData* data, int frame);
	void draw(MeshData* data, float elapsedTime, int startFrame, int lastFrame);
	
	float nextFrame;
	int curFrame;
	
};

#endif /*MD3RENDERER_H_*/
