
#include <GL/gl.h>
#include "objRenderer.h"
#include "../../../util/meshio/obj/objData.h"

void ObjRenderer::draw(MeshData* data){
	
	ObjData* objdata = (ObjData*) data;
	
	glVertexPointer(3, GL_FLOAT, 0, objdata->vertexdata);
	glNormalPointer(GL_FLOAT, 0, objdata->normaldata);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glDrawElements(GL_TRIANGLES, objdata->nindices, GL_UNSIGNED_INT, objdata->indices);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}