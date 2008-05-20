#include <GL/gl.h>
#include <iostream>
#include "StaticEntity.h"
/*#include "../datamanager/DataManager.h"
#include "../renderer/Renderer.h"

bool StaticEntity::initialize(char* filename){
	
	//carregou os meshes agora 
	mesh = (MeshIO*) DATAMANAGER::getInstance().loadMesh(filename);
	if (!mesh)
		return false;
				
	return true;
}

void StaticEntity::draw(){
	
	std::list<MeshData* >::iterator iter2 = mesh->meshes.begin();
	//RENDERER::getInstance().resetStates();
	RENDERER::getInstance().applyVertexFormat(mesh->vfs[0]);
	RENDERER::getInstance().applyVertexBuffer(0, mesh->vbos[0]);
	RENDERER::getInstance().applyIndexBuffer(mesh->ibs[0]);
	
	glDrawElements(GL_TRIANGLES, (*iter2)->nindices, GL_UNSIGNED_INT, 0);
	
}*/
