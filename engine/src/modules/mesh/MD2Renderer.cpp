
#include "MD2Renderer.h"
#include "../../util/meshio/md2/md2IO.h"
#include "../timer/timer.h"
#include <GL/gl.h>

void MD2Renderer::draw(MeshData* data){
}

void MD2Renderer::draw(MeshData* data, float elapsedTime, int startframe, int lastframe){
	
	unsigned long time1 = TIMER::getInstance().getCurrentTime();
		
	if(time1 > nextFrame)
     {
        curFrame++;
        nextFrame = time1 + 200;
         
         if(curFrame >= lastframe)
          curFrame = startframe;
      }
	draw(data, curFrame);
}
void MD2Renderer::draw(MeshData* data, int frame){
	
	MD2Obj* md2data = (MD2Obj*) data;
	
	int Part;
 
	if(frame >= md2data->getFrameCount())
		frame=0;
 
	glBegin(GL_TRIANGLES);  
 
	for(Part=0; Part < md2data->getTotalFaces(); ++Part){
	//	glNormal3f( md2data->frame[frame].Norm[Part].x, md2data->frame[frame].Norm[Part].y, md2data->frame[frame].Norm[Part].z);
	
		glTexCoord2f(md2data->texcoords[md2data->face[Part].uv1].u, md2data->texcoords[md2data->face[Part].uv1].v);
		glVertex3f(md2data->frame[frame].Vtx[md2data->face[Part].p1].x, md2data->frame[frame].Vtx[md2data->face[Part].p1].y, md2data->frame[frame].Vtx[md2data->face[Part].p1].z);
	
		glTexCoord2f(md2data->texcoords[md2data->face[Part].uv2].u, md2data->texcoords[md2data->face[Part].uv2].v);
		glVertex3f(md2data->frame[frame].Vtx[md2data->face[Part].p2].x, md2data->frame[frame].Vtx[md2data->face[Part].p2].y, md2data->frame[frame].Vtx[md2data->face[Part].p2].z);
	
		glTexCoord2f(md2data->texcoords[md2data->face[Part].uv3].u, md2data->texcoords[md2data->face[Part].uv3].v);
		glVertex3f(md2data->frame[frame].Vtx[md2data->face[Part].p3].x, md2data->frame[frame].Vtx[md2data->face[Part].p3].y, md2data->frame[frame].Vtx[md2data->face[Part].p3].z);
	}  
 
	glEnd();
	
}
