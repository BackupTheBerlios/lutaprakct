
#include "meshRenderer.h"
#include "MD2Renderer.h"

MeshRenderer* getMeshRenderer(int rendererType){

	MeshRenderer* ret;
	if (rendererType == MD2RENDERER){
		ret = new MD2Renderer();
		return ret;
	}
	return NULL;
	
}
