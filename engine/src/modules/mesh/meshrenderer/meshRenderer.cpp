
#include "meshRenderer.h"
#include "MD2Renderer.h"
#include "objRenderer.h"

MeshRenderer* getMeshRenderer(int rendererType){

	MeshRenderer* ret;
	if (rendererType == MD2RENDERER){
		ret = new MD2Renderer();
		return ret;
	} else if (rendererType == OBJRENDERER){
		ret = new ObjRenderer();
		return ret;
	}else{
		return NULL;
	}
	
}
