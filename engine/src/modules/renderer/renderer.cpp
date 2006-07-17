
#include<GL/gl.h>
#include<GL/glu.h>
#include "renderer.h"
#include "../timer/timer.h"
#include "../../util/logger/logger.h"
#include "../../util/math/algebra.h"
#include "../../util/glhelper/glextensions.h"

#include "../effects/fog/fog.h"
#include "../mesh/skydome/skydome.h"

#include "../shaders/cgshaders/cgTerrainSplat.h"

#include <iostream>

GLuint terrainTexID;
Fog* f;
texture* t;
texture* t2;
texture* alpha;

Skydome* dome;
cgTerrainSplat* splatcg;

const char* splatFragmentSource =
"uniform sampler2D tex0;																			\n"
"uniform sampler2D tex1;																			\n"
"void main(){																						\n"
"    vec3  vectex0  = vec3(texture2D(tex0, gl_TexCoord[0].xy));										\n"
"    vec3  vectex1  = vec3(texture2D(tex1, gl_TexCoord[0].xy));										\n"
"    gl_FragColor = vec4(vectex0, 1.0);																\n"
"}																									\n\0";

void RenderOctreeNode(Octree* pNode)
{
   if(pNode == NULL) return;

   if(pNode->isLeafNode())
      {
         if(!pNode->isVertices()) return;

         int numTris = pNode->getNumTriangles();

         // Get the min and max bounding box for this node.
         float bbSize = pNode->getBoundingBoxSize();

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

         // Apply the textures.
		/* glActiveTextureARB(GL_TEXTURE0_ARB);
		 glEnable(GL_TEXTURE_2D);
		 glBindTexture(GL_TEXTURE_2D, t->getId());
       
         glActiveTextureARB(GL_TEXTURE1_ARB);
         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D, t2->getId());

		 glActiveTextureARB(GL_TEXTURE0_ARB);                
         //glActiveTextureARB(GL_TEXTURE2_ARB);
         //glEnable(GL_TEXTURE_2D);
         //glBindTexture(GL_TEXTURE_2D, alpha->getId());

         //glActiveTextureARB(GL_TEXTURE0_ARB);
         //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
         //glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);

         glEnableClientState(GL_VERTEX_ARRAY);
    		 glClientActiveTextureARB(GL_TEXTURE0_ARB);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         
         glVertexPointer(3, GL_FLOAT, 0, pVerts);
         glTexCoordPointer(2, GL_FLOAT, 0, pTC1);
   
         glClientActiveTextureARB(GL_TEXTURE1_ARB);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         glTexCoordPointer(2, GL_FLOAT, 0, pTC1);
         glClientActiveTextureARB(GL_TEXTURE0_ARB);
         
//         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
 //        glTexCoordPointer(2, GL_FLOAT, 0, pTC2);
 //        glClientActiveTextureARB(GL_TEXTURE0_ARB);
         
         // Draw the entire node's data.
         //glColor3f(1.0, 0.0, 0.0);
         glDrawArrays(GL_TRIANGLES, 0, numTris * 3);

         // Disable all the client states we enabled.
         glDisableClientState(GL_VERTEX_ARRAY);
		 glClientActiveTextureARB(GL_TEXTURE0_ARB);
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
         
//         glClientActiveTextureARB(GL_TEXTURE1_ARB);
 //        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
 
         glClientActiveTextureARB(GL_TEXTURE1_ARB);
         glDisable(GL_TEXTURE_2D);
         glClientActiveTextureARB(GL_TEXTURE0_ARB);
         glDisable(GL_TEXTURE_2D);
         
         glColor4f(1.0, 1.0, 1.0, 1.0);*/
         
         /*
         //ultima versao:
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, t->getId());
       // t->enable();
       // t->bind();

         glActiveTextureARB(GL_TEXTURE1_ARB);
         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D, t2->getId());
         
         //glActiveTextureARB(GL_TEXTURE2_ARB);
         //glEnable(GL_TEXTURE_2D);
         //glBindTexture(GL_TEXTURE_2D, t2->getId());

        // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
         //glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);

         glActiveTextureARB(GL_TEXTURE0_ARB);
         // Set pointers.
         glEnableClientState(GL_VERTEX_ARRAY);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);

         glVertexPointer(3, GL_FLOAT, 0, pVerts);
         glTexCoordPointer(2, GL_FLOAT, 0, pTC1);
         
         glClientActiveTextureARB(GL_TEXTURE1_ARB);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         glTexCoordPointer(2, GL_FLOAT, 0, pTC2);
         
         glClientActiveTextureARB(GL_TEXTURE0_ARB);

         //glClientActiveTextureARB(GL_TEXTURE2_ARB);
         //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         //glTexCoordPointer(2, GL_FLOAT, 0, pTC1);

         // Draw the entire node's data.
         //glColor3f(1.0, 0.0, 0.0);
         glDrawArrays(GL_TRIANGLES, 0, numTris * 3);

         // Disable all the client states we enabled.
         glDisableClientState(GL_VERTEX_ARRAY);
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
         
         //t->unbind();
		//glActiveTextureARB(GL_TEXTURE2_ARB);
		//glDisable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, 0);
		
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
        
         glClientActiveTextureARB(GL_TEXTURE1_ARB);
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
         glClientActiveTextureARB(GL_TEXTURE0_ARB);
*/         
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, t->getId());
       // t->enable();
       // t->bind();

         glActiveTextureARB(GL_TEXTURE1_ARB);
         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D, t2->getId());
         
         glActiveTextureARB(GL_TEXTURE2_ARB);
         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D, alpha->getId());

        // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
         //glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);

         glActiveTextureARB(GL_TEXTURE0_ARB);
         // Set pointers.
         glEnableClientState(GL_VERTEX_ARRAY);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);

         glVertexPointer(3, GL_FLOAT, 0, pVerts);
         glTexCoordPointer(2, GL_FLOAT, 0, pTC1);
         
         glClientActiveTextureARB(GL_TEXTURE1_ARB);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         glTexCoordPointer(2, GL_FLOAT, 0, pTC1);
         
         glClientActiveTextureARB(GL_TEXTURE0_ARB);

         glClientActiveTextureARB(GL_TEXTURE2_ARB);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         glTexCoordPointer(2, GL_FLOAT, 0, pTC2);

         // Draw the entire node's data.
         //glColor3f(1.0, 0.0, 0.0);
         glDrawArrays(GL_TRIANGLES, 0, numTris * 3);

         // Disable all the client states we enabled.
         glDisableClientState(GL_VERTEX_ARRAY);
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
         
         //t->unbind();
		glActiveTextureARB(GL_TEXTURE2_ARB);
		glDisable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, 0);
		
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, 0);

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glDisable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, 0);
        
         glClientActiveTextureARB(GL_TEXTURE1_ARB);
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
         glClientActiveTextureARB(GL_TEXTURE2_ARB);
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
         glClientActiveTextureARB(GL_TEXTURE0_ARB);

      }
   else
      {
         // Else if this node is not a leaf then
         // we continue down the tree.
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
    
    //inicializacao dos flags que as texturas vao usar
    std::cout << "Inicializando texture manager... ";
	TEXTUREMANAGER::getInstance().setDefaultFlags();
	std::cout << "Pronto" << std::endl;

	//inicializacao das extensions
	std::cout << "Inicializando OpenGL extensions... ";
	initializeExtensions();
	std::cout << "Pronto" << std::endl;

	if(!terrain.loadMap("map.raw", 4))
		std::cout << "Nao foi possivel ler o mapa" << std::endl;

//	CAMERA::getInstance().initialize();

/*
   	if(!terrain.loadTile(LOWEST_TILE, "lowest2.tga")) return false;
	if(!terrain.loadTile(LOW_TILE, "low2.tga")) return false;
	if(!terrain.loadTile(HIGH_TILE, "high2.tga")) return false;
	if(!terrain.loadTile(HIGHEST_TILE, "highest2.tga")) return false;

	unsigned char *image = NULL;

	image = terrain.generateTextureMap(512);
	if(!image) return false;

   // Load both textures.
	glGenTextures(1, &terrainTexID);
	glBindTexture(GL_TEXTURE_2D, terrainTexID);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8);					
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512,
	             0, GL_RGB, GL_UNSIGNED_BYTE, image);
*/
	f = new Fog(58.0f / 255, 68.0f / 255, 184.0f / 255, 1.0,  0.03, 0.0, 100.0,  FOG_EXP2);
	std::cout << "Inicializando Skydome...";
	dome = new Skydome("sky2.tga", 32, 48, 1000.0, COLORED_SKY | ANIMATED_CLOUDS ,0.4);
	dome->setCoordinates(44.0, 36.0, 6.0, 180.0);
    dome->update(0);
	std::cout << "Pronto!" << std::endl;
	
	std::cout << "Inicializando texturas... ";
	t = TEXTUREMANAGER::getInstance().load("bottom.tga", texture::TEXTURE_2D, texture::RGB, texture::RGB8, texture::ANISOTROPIC_4);
	t2 = TEXTUREMANAGER::getInstance().load("mid2.tga", texture::TEXTURE_2D, texture::RGB, texture::RGB8, texture::ANISOTROPIC_4);
	alpha = TEXTUREMANAGER::getInstance().load("alphamap4.tga", texture::TEXTURE_2D, texture::RGBA, texture::RGBA8, 0);
	std::cout << "Pronto." <<std::endl;
	
   	CAMERA::getInstance().setPosition(100.07f, 124.641f, 50.5f, 108.0f, 124.0f, 50.0f, 0.0f, 1.0f, 0.0f);
	
//	splat = new terrainSplat(NULL, splatFragmentSource );
//	splat->setInitialParameters();
	//std::cout << "Splat shader: " << splat->getCompilerLog() << std::endl;
	std::cout << "Inicializando terrain shader...";
	splatcg = new cgTerrainSplat(NULL, 0, "terrainSplatting.cg", PROFILE_ARBFP1, 0);
	splatcg->compile();
//	splatcg->setTexId(t->getId(), t2->getId());
	std::cout << "Pronto." << std::endl;
	std::cout << "Renderer inicializado com sucesso." << std::endl;
	return true;
	
}

void Renderer::update(void* data){

	video->lock();
//	std::cout << "renderer main loop" << std::endl;
	/*loop em todas entidades visiveis pra desenha-las*/
//	CAMERA::getInstance().update(0.1);
//	std::cout << "fps " << TIMER::getInstance().getFPS() << " 1/fps " << 1.0/(TIMER::getInstance().getFPS()) << std::endl;
//	vec3 cameraPosition = CAMERA::getInstance().getPosition();
//	std::cout <<  "camera position: " << cameraPosition.x << " " << cameraPosition.y << " " << cameraPosition.z << std::endl;
   gluLookAt(CAMERA::getInstance().xPos, CAMERA::getInstance().yPos, CAMERA::getInstance().zPos,
             CAMERA::getInstance().xView, CAMERA::getInstance().yView, CAMERA::getInstance().zView,
             CAMERA::getInstance().xUp, CAMERA::getInstance().yUp, CAMERA::getInstance().zUp);
             
  //  std::cout << CAMERA::getInstance().xPos << " " << CAMERA::getInstance().yPos << " " << CAMERA::getInstance().zPos << " " << CAMERA::getInstance().xView << " " << CAMERA::getInstance().yView << " " << CAMERA::getInstance().zView <<" " << CAMERA::getInstance().xUp << " "<< CAMERA::getInstance().yUp << " "<< CAMERA::getInstance().zUp << std::endl;
/*	f->bind();*/
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glTranslatef(0.0, 0.0, 0.0);
	dome->draw();
	//f->bind();
	glTranslatef(0.0, 100.0, 0.0);
	splatcg->bind();
	RenderOctreeNode(terrain.rootNode);
	splatcg->unbind();
	
	//f->unbind();
	video->unlock();
	
}
