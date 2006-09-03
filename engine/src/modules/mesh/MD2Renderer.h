#ifndef MD2RENDERER_H_
#define MD2RENDERER_H_

#include "meshRenderer.h"

class MD2Renderer : public MeshRenderer{
	
public:
	
	MD2Renderer(){};
	~MD2Renderer(){};
	
	void draw(MeshData* data);
	void draw(MeshData* data, int frame);
	
};

#endif /*MD3RENDERER_H_*/
