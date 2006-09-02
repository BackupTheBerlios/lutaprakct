#ifndef MESHRENDERER_H_
#define MESHRENDERER_H_

#include "meshData.h"

class MeshRenderer{
	
public:
	
	MeshRenderer(){};
	virtual ~MeshRenderer(){};
	
	void draw(MeshData* data) = 0;
	void draw(MeshData* data, int frame) = 0;
	
};

#endif /*MESHRENDERER_H_*/
