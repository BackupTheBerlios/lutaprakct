
#include<GL/gl.h>
#include<GL/glu.h>
#include "renderer.h"
#include "../timer/timer.h"
#include "../../util/logger/logger.h"
#include "../../util/math/algebra.h"
#include "../../util/glhelper/glextensions.h"
#include "../../util/image/tgaimage.h"

#include "../effects/fog/fog.h"
#include "../mesh/skydome/skydome.h"

#include "../shaders/cgshaders/cgTerrainSplat.h"

#include "../../util/meshio/md2/md2IO.h"
#include "../../util/meshio/obj/objload.h"
#include "../material/basicTextureMaterial.h"

#include "../gui/font.h"
#include "../gui/windowimage.h"

#include "../mesh/mesh.h"

#include <iostream>

GLuint terrainTexID;
texture* t;
texture* t2;
texture* alpha;

Skydome* dome;
cgTerrainSplat* splatcg;

BasicTextureMaterial knightskin;

//Font testfont;
//WindowImage testwin;
	Frustum frustum;
Mesh knight;

//dados pro disco
unsigned int nverts = 0;
unsigned int nindices = 0;
unsigned int *indices = NULL;
float *vertexdata = NULL;
float *normaldata = NULL;
float *tangentdata = NULL;
float *binormaldata = NULL;
float *texcoords = NULL;

GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };


/*const char* splatFragmentSource =
"uniform sampler2D tex0;																			\n"
"uniform sampler2D tex1;																			\n"
"void main(){																						\n"
"    vec3  vectex0  = vec3(texture2D(tex0, gl_TexCoord[0].xy));										\n"
"    vec3  vectex1  = vec3(texture2D(tex1, gl_TexCoord[0].xy));										\n"
"    gl_FragColor = vec4(vectex0, 1.0);																\n"
"}																									\n\0";
*/
void RenderOctreeNode(Octree* pNode){
	if(pNode == NULL) return;

	float bbSize = pNode->getBoundingBoxSize();
	bbSize /= 2.0;
	float centerx, centery, centerz;
	pNode->getBoundingBoxCenter(centerx, centery, centerz);

	if (!frustum.cubeInFrustum(centerx, centery, centerz, bbSize))
		return;

	if(pNode->isLeafNode()){
			
		if(!pNode->isVertices()) return;

		int numTris = pNode->getNumTriangles();

         // Get the min and max bounding box for this node.

         float bbMin[3];
         pNode->getBoundingBoxCenter(bbMin[0], bbMin[1], bbMin[2]);
         bbMin[0] -= bbSize / 2.0f;
         bbMin[1] -= bbSize / 2.0f;
         bbMin[2] -= bbSize / 2.0f;

         float bbMax[3];
         pNode->getBoundingBoxCenter(bbMax[0], bbMax[1], bbMax[2]);
         bbMax[0] += bbSize / 2.0f;
         bbMax[1] += bbSize / 2.0f;
         bbMax[2] += bbSize / 2.0f;

         // Draw the bounding box for debug purposes.
         //DrawBoundingBox(bbMin, bbMax);

         // Get the data so we can render it out.
         float *pVerts = pNode->getVertices();
         float *pTC1 = pNode->getTexCoord1();
         float *pTC2 = pNode->getTexCoord2();

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, t->getId());

        glActiveTextureARB(GL_TEXTURE1_ARB);
         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D, t2->getId());
         
         glActiveTextureARB(GL_TEXTURE2_ARB);
         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D, alpha->getId());


         glActiveTextureARB(GL_TEXTURE0_ARB);
         // Set pointers.
         glEnableClientState(GL_VERTEX_ARRAY);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);

//        glVertexPointer(3, GL_FLOAT, 0, pVerts);
         pNode->vert.bind();
         glVertexPointer(3, GL_FLOAT, 0, NULL);
         pNode->texcoord1.bind();
         glTexCoordPointer(2, GL_FLOAT, 0, NULL);
//		glTexCoordPointer(2, GL_FLOAT, 0, pTC1);
         
         glClientActiveTextureARB(GL_TEXTURE1_ARB);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//         glTexCoordPointer(2, GL_FLOAT, 0, pTC1);
         pNode->texcoord2.bind();
         glTexCoordPointer(2, GL_FLOAT, 0, NULL);
         
         glClientActiveTextureARB(GL_TEXTURE0_ARB);

         glClientActiveTextureARB(GL_TEXTURE2_ARB);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//         glTexCoordPointer(2, GL_FLOAT, 0, pTC2);
         pNode->texcoord2.bind();
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

         // Draw the entire node's data.
         //glColor3f(1.0, 0.0, 0.0);


         glDrawArrays(GL_TRIANGLES, 0, numTris * 3);
         pNode->vert.unbind();

         // Disable all the client states we enabled.
         glDisableClientState(GL_VERTEX_ARRAY);
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
         
		glActiveTextureARB(GL_TEXTURE2_ARB);
		glDisable(GL_TEXTURE_2D);
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable(GL_TEXTURE_2D);
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glDisable(GL_TEXTURE_2D);
        
         glClientActiveTextureARB(GL_TEXTURE1_ARB);
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
         glClientActiveTextureARB(GL_TEXTURE2_ARB);
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
         glClientActiveTextureARB(GL_TEXTURE0_ARB);

      
	}
   else
   {
         Octree **pSubNodes = pNode->getSubNodes();
         RenderOctreeNode(pSubNodes[TOP_FRONT_LEFT]);
         RenderOctreeNode(pSubNodes[TOP_FRONT_RIGHT]);
         RenderOctreeNode(pSubNodes[TOP_BACK_LEFT]);
         RenderOctreeNode(pSubNodes[TOP_BACK_RIGHT]);

         RenderOctreeNode(pSubNodes[BOTTOM_FRONT_LEFT]);
         RenderOctreeNode(pSubNodes[BOTTOM_FRONT_RIGHT]);
         RenderOctreeNode(pSubNodes[BOTTOM_BACK_LEFT]);
         RenderOctreeNode(pSubNodes[BOTTOM_BACK_RIGHT]);
    }
}

void Renderer::stop(void* data){
}

bool Renderer::start(void* data){

	//inicializa??o basica do video
	video =  initializeVideo(videoSystem::VIDEO_SDL);
	if (video == NULL)
		return false;
	if (!video->initialize( videoSystem::RES_800x600 | videoSystem::BPP_8 | videoSystem::OPENGL ))
		return false;
	video->setWindowTitle("Engine");
    video->showCursor(false);
    
    //inicializacao dos flags que as texturas vao usar;
	TEXTUREMANAGER::getInstance().setDefaultFlags();

	//inicializacao das extensions
	initializeExtensions();

	std::cout << "Inicializando Skydome...";
	dome = new Skydome("sky2.tga", 32, 48, 1000.0, COLORED_SKY | SKY_ELEMENTS, 0.1);
	dome->setCoordinates(44.0, 36.0, 6.0, 180.0);
    dome->update(0);
	std::cout << "Pronto!" << std::endl;

	terrain.loadMap("lol", 8);

	//f = new Fog(58.0f / 255, 68.0f / 255, 184.0f / 255, 1.0,  0.03, 0.0, 100.0,  FOG_EXP2);
	
	std::cout << "Inicializando texturas... ";
	t = TEXTUREMANAGER::getInstance().load("bottom.tga", texture::TEXTURE_2D, texture::RGB, texture::RGB8, 0);
	t2 = TEXTUREMANAGER::getInstance().load("mid2.tga", texture::TEXTURE_2D, texture::RGB, texture::RGB8, 0);
	alpha = TEXTUREMANAGER::getInstance().load("alphamap4.tga", texture::TEXTURE_2D, texture::RGBA, texture::RGBA8, 0);
	std::cout << "Pronto." <<std::endl;
	
   	CAMERA::getInstance().setPosition(100.07f, 24.641f, 50.5f, 108.0f, 24.0f, 50.0f, 0.0f, 1.0f, 0.0f);
	
	std::cout << "Inicializando terrain shader...";
	splatcg = new cgTerrainSplat(NULL, 0, "terrainSplatting.cg", PROFILE_ARBFP1, 0);
	splatcg->compile();
	std::cout << "Pronto." << std::endl;
	
//	for (int i = 0; i < 100; i++)
//		for (int k = 0; k < 100; k++)
//			std::cout << (float)  terrain.getHeight(i, k) << std::endl;
	
	float height = (float)  terrain.getScaledHeight(50, 51);
	knight.initialize("knight.md2");
	knightskin.initialize("knightskin2.tga");
	//knight.translateTo(50.0, (100.0 + height), 51.0);
//	knight.scale(0.1, 0.1, 0.1);	
	
	//std::cout << "inicializando fonte " << std::endl;
	//testfont.initialize("font.tga");
//	testwin.initialize(200, 400, 100, 100, false);
//	testwin.setTexture("background.tga");
//	testwin.setBorder("bottomgump.tga", "topgump.tga", "right.tga", "left.tga", "bottomright.tga", "bottomleft.tga", "topright.tga", "topleft.tga", 40);
	
	LoadObjModel( "ufo.obj",nverts, nindices, indices, vertexdata, normaldata, tangentdata, binormaldata, texcoords );
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);		
	
	std::cout << "Renderer inicializado com sucesso." << std::endl;
	return true;
}

void Renderer::update(void* data){

	video->lock();
	/*loop em todas entidades visiveis pra desenha-las*/
   gluLookAt(CAMERA::getInstance().xPos, CAMERA::getInstance().yPos, CAMERA::getInstance().zPos,
             CAMERA::getInstance().xView, CAMERA::getInstance().yView, CAMERA::getInstance().zView,
             CAMERA::getInstance().xUp, CAMERA::getInstance().yUp, CAMERA::getInstance().zUp);
   // std::cout << CAMERA::getInstance().xPos << " " << CAMERA::getInstance().yPos << " " << CAMERA::getInstance().zPos << " " << CAMERA::getInstance().xView << " " << CAMERA::getInstance().yView << " " << CAMERA::getInstance().zView <<" " << CAMERA::getInstance().xUp << " "<< CAMERA::getInstance().yUp << " "<< CAMERA::getInstance().zUp << std::endl;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPushMatrix();
	//glTranslatef(0.0, -150.0, 0.0);
	//dome->draw();
	//glPopMatrix();
	//mat4 modelview;
	//modelview[13] = 100;
	//glLoadMatrixf(modelview.mat_array);
	//glTranslatef(0.0, 100.0, 0.0);

	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	float height = (float)terrain.getScaledInterpolatedHeight(50, 50);
	//std::cout << "height " << height << std::endl;
	glTranslatef(50, height+24, 50);
	glRotatef(90, -1.0, 0.0, 0.0);
	knightskin.bind();
	knight.draw(50);
	knightskin.unbind();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100, 30, 50);
	glRotatef(30, 1.0, 1.0, 0.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glVertexPointer(3, GL_FLOAT, 0, vertexdata);
	glNormalPointer(GL_FLOAT, 0, normaldata);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glDrawElements(GL_TRIANGLES, nindices, GL_UNSIGNED_INT, indices);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(105, 35, 60);
	glRotatef(60, 1.0, 0.0, 0.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glVertexPointer(3, GL_FLOAT, 0, vertexdata);
	glNormalPointer(GL_FLOAT, 0, normaldata);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glDrawElements(GL_TRIANGLES, nindices, GL_UNSIGNED_INT, indices);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(110, 35, 55);
	glRotatef(20, 1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glVertexPointer(3, GL_FLOAT, 0, vertexdata);
	glNormalPointer(GL_FLOAT, 0, normaldata);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glDrawElements(GL_TRIANGLES, nindices, GL_UNSIGNED_INT, indices);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	//necessario chamar o update sempre q a matriz muda
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	frustum.update();
	splatcg->bind();
	RenderOctreeNode(terrain.rootNode);
	splatcg->unbind();
	glPopMatrix();
	
//setup2dRendering();

	video->unlock();
	
}

void Renderer::handleEvent(const event& e){
	
	switch (e.type){
		case E_KEY_F1:
				int viewport[4];
				glGetIntegerv(GL_VIEWPORT, viewport);
				unsigned char* data = NULL;
				data =  new unsigned char[3 * viewport[2] * viewport[3]];
				glPixelStorei(GL_PACK_ALIGNMENT,1);
				glReadBuffer(GL_FRONT);
				glReadPixels(0,0, viewport[2], viewport[3], GL_RGB, GL_UNSIGNED_BYTE, data);
				tgaimage img;
				img.write("screenshot.tga", viewport[2], viewport[3], 24, data);
				delete data;
			break;
	}
	
}

void Renderer::setup2dRendering(){
	
		glPushAttrib(GL_ALL_ATTRIB_BITS); 
		glPushMatrix();		
		
//		glGetFloatv( GL.GL_PROJECTION_MATRIX, matrixProjectionOld, 0 );
	
		glEnable(GL_TEXTURE_2D); 
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST); 
		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho( 0, 800, 600, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();			
					
		//testfont.print(10, 10, "Forge an Empire");	
		//testwin.draw();
		//testfont.print(80, 100, "Insane Races");
		
		glPopMatrix();
		glPopAttrib();
		
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		
		glMatrixMode(GL_MODELVIEW);
	
}

