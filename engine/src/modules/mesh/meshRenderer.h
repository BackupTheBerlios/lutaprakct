#ifndef MESHRENDERER_H_
#define MESHRENDERER_H_

#include "meshData.h"

/*mesh renderer ? uma interface pro tipo de renderer, que pode variar
 * de acordo com o tipo de modelo e como ele vai ser desenhado
 * pelo opengl
 * */

enum {
	MD2RENDERER = 1,
	OBJRENDERER = 2
};

class MeshRenderer{
	
public:
	
	MeshRenderer(){};
	virtual ~MeshRenderer(){};
	
	virtual void draw(MeshData* data) = 0;
	virtual void draw(MeshData* data, int frame) = 0;
	
};

MeshRenderer* getMeshRenderer(int rendererType);

#endif /*MESHRENDERER_H_*/
