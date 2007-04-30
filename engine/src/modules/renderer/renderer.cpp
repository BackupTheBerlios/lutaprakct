
#include<GL/gl.h>
#include<GL/glu.h>
#include <cmath>
#include <list>
#include <iostream>
#include "renderer.h"
#include "../timer/timer.h"
#include "../../../libs/tinyxml/tinyxml.h"
#include "../material/materialFactory.h"
#include "../light/light.h"
#include "../light/lightManager.h"
#include "../../util/logger/logger.h"
#include "../../util/image/tgaimage.h"

void Renderer::stop(void* data){
}

bool Renderer::start(void* data){

	screenShotNumber = 0;
	
	video =  initializeVideo(VideoSystem::VIDEO_SDL);
	if (video == NULL)
		return false;
	if (!video->initialize( VideoSystem::BPP_8 | VideoSystem::OPENGL ))
		return false;
    
	TEXTUREMANAGER::getInstance().setDefaultFlags();

	//carrega o XML
	TiXmlDocument configdoc("config.xml");
	if (!configdoc.LoadFile()){
		std::cout << "(Renderer)ERRO: Arquivo de configuracao config.xml nao encontrado." << std::endl;
		configdoc.Clear();
		return false;
	}
	TiXmlElement* enginecfg = configdoc.FirstChildElement("engine");
	TiXmlElement* scenecfg = enginecfg->FirstChildElement("scene");
	
	if (scenecfg){ //lendo a cena no cfg se tiver alguma
		
		//verifica se tem luzes no xml
		TiXmlElement* lightscfg = scenecfg->FirstChildElement("lights");
		TiXmlElement* lightcfg = lightscfg->FirstChildElement("light");
		//while(lightcfg){
		if (lightcfg){
			Light* light = new Light();
			TiXmlElement* positioncfg = lightcfg->FirstChildElement("position");
			if (positioncfg)
				light->setPosition( atof(positioncfg->Attribute("x")),
									 atof(positioncfg->Attribute("y")),
									 atof(positioncfg->Attribute("z")),
									 atof(positioncfg->Attribute("w")));
			TiXmlElement* diffusecfg = lightcfg->FirstChildElement("diffuse");
			if (diffusecfg)
				light->setDiffuse( atof(diffusecfg->Attribute("r")),
									 atof(diffusecfg->Attribute("g")),
									 atof(diffusecfg->Attribute("b")),
									 atof(diffusecfg->Attribute("a")));
			TiXmlElement* ambientcfg = lightcfg->FirstChildElement("ambient");
			if (ambientcfg)
				light->setAmbient( atof(ambientcfg->Attribute("r")),
									 atof(ambientcfg->Attribute("g")),
									 atof(ambientcfg->Attribute("b")),
									 atof(ambientcfg->Attribute("a")));
			light->initialize( atoi(lightcfg->Attribute("id")) );
			LIGHTMANAGER::getInstance().add(light);
			lightcfg->NextSiblingElement();
		}
		
		//skybox
		TiXmlElement* skycfg = scenecfg->FirstChildElement("sky");
		if (skycfg){ //se tiver sky
			TiXmlElement* skyboxcfg = skycfg->FirstChildElement("skybox");
			if(skyboxcfg){ //se tiver skybox configura ele
				std::string defaultbackground(skyboxcfg->Attribute("defaultbackground"));
				sky.initialize( defaultbackground, 
								atof(skyboxcfg->Attribute("size")),
								atoi(skyboxcfg->Attribute("followcamera")),
								atoi(skyboxcfg->Attribute("enabled")) );
			}
		}

		TiXmlElement* mapcfg = scenecfg->FirstChildElement("map");
		//TODO terreno mais elaborado com opcoes de especificar shaders e material
		//adicionar outros heightmaps e setar como base dos meshes
		if (mapcfg){
			TiXmlElement* heightmapcfg = mapcfg->FirstChildElement("heightmap");
			terrain.loadMap( (char*)heightmapcfg->Attribute("filename"), 
							atoi(heightmapcfg->Attribute("texrepeat")));
			geometry = new Octree();
			geometry->initialize(terrain.vertex, terrain.totalVerts, terrain.texCoords, 
								terrain.texCoords2, 20, 5000);
			terrain.shutDown();
			
			//procura o file de material do terreno
			TiXmlElement* filescfg = mapcfg->FirstChildElement("files");
			if (filescfg){
				std::string materialFileName = filescfg->Attribute("material");
				Material* terrainMaterial = MaterialFactory::loadMaterial(materialFileName);
				terrain.setMaterial(terrainMaterial);
			}
			
		}

		//carrega os meshes
		//TODO carregar material dos meshes
		TiXmlElement* meshescfg = scenecfg->FirstChildElement("meshes");
		if (meshescfg){
			TiXmlElement* meshcfg = meshescfg->FirstChildElement("mesh");
			while (meshcfg){
				TiXmlElement* filecfg = meshcfg->FirstChildElement("files");
				TiXmlElement* rotatecfg = meshcfg->FirstChildElement("rotate");
				TiXmlElement* translatecfg = meshcfg->FirstChildElement("translate");
				Mesh* mesh = new Mesh();
				mesh->initialize(filecfg->Attribute("geometryfile"));
				std::string materialFileName = filecfg->Attribute("material");
				if (materialFileName != ""){
					Material* meshMaterial = MaterialFactory::loadMaterial(materialFileName);
					mesh->setMaterial(meshMaterial);
				}
				if (rotatecfg)
					mesh->rotate(atof(rotatecfg->Attribute("angle")),
								atof(rotatecfg->Attribute("x")),	
								atof(rotatecfg->Attribute("y")),
								atof(rotatecfg->Attribute("z")));
				if (translatecfg)
					mesh->translateTo(atof(translatecfg->Attribute("x")),
										atof(translatecfg->Attribute("y")),
										atof(translatecfg->Attribute("z")));
				meshes.push_back(mesh);
				meshcfg = meshcfg->NextSiblingElement();
			}
		}
		
		TiXmlElement* cameracfg = enginecfg->FirstChildElement("camera");
		if (cameracfg){
			TiXmlElement* vectorscfg = cameracfg->FirstChildElement("vectors");
			CAMERA::getInstance().setPosition(atof(vectorscfg->Attribute("xpos")),
													atof(vectorscfg->Attribute("ypos")),
													atof(vectorscfg->Attribute("zpos")),
													atof(vectorscfg->Attribute("xview")),
													atof(vectorscfg->Attribute("yview")),
													atof(vectorscfg->Attribute("zview")),
													0.0f, 1.0f, 0.0f);
		}
		
	}
	
	configdoc.Clear();		
	
	std::cout << "Renderer inicializado com sucesso." << std::endl;
	
	return true;
}

void Renderer::update(void* data){

	video->lock(); //clear no color e depth buffer
	
	float elapsedTime =  TIMER::getInstance().getElapsedTime(); //pega o tempo q passou
	//posiciona a camera
	gluLookAt(CAMERA::getInstance().xPos, CAMERA::getInstance().yPos, CAMERA::getInstance().zPos,
             CAMERA::getInstance().xView, CAMERA::getInstance().yView, CAMERA::getInstance().zView,
             CAMERA::getInstance().xUp, CAMERA::getInstance().yUp, CAMERA::getInstance().zUp);
	
	if (sky.isEnabled())
		sky.draw();
	
	//para todos os meshs na cena, updatea eles e depois desenha
	//TODO colocar esses meshes na octree
	std::list<Mesh*>::iterator iter;
	LIGHTMANAGER::getInstance().bind();
	for ( iter = meshes.begin(); iter != meshes.end(); iter++){
		(*iter)->update(elapsedTime);
		(*iter)->draw();
	}
	LIGHTMANAGER::getInstance().unbind();

	//desenha o terreno
	glPushMatrix();
	frustum.update();
	terrain.bindMaterial();
	drawOctree(geometry);
	terrain.unbindMaterial();
	glPopMatrix();
	
	video->unlock();
	
}

void Renderer::handleEvent(const event& e){
	
	switch (e.type){
		case E_KEY_F1:
				//unsigned char idteste = '1';
				int viewport[4];
				glGetIntegerv(GL_VIEWPORT, viewport);
				unsigned char* data = NULL;
				data =  new unsigned char[3 * viewport[2] * viewport[3]];
				glPixelStorei(GL_PACK_ALIGNMENT,1);
				glReadBuffer(GL_FRONT);
				glReadPixels(0,0, viewport[2], viewport[3], GL_RGB, GL_UNSIGNED_BYTE, data);
				TgaImage img;
				char filename[50];
				if (screenShotNumber < 10)
					sprintf(filename, "img_00%d.tga", screenShotNumber );
				else if (screenShotNumber <= 99 )
					sprintf(filename, "img_0%d.tga", screenShotNumber );
				else
					sprintf(filename, "img_%d.tga", screenShotNumber );
				std::string file(filename);
				img.write(file, viewport[2], viewport[3], 24, data);
				screenShotNumber++;
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
					
		//desenha aqui
		
		glPopMatrix();
		glPopAttrib();
		
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		
		glMatrixMode(GL_MODELVIEW);
	
}

void Renderer::drawOctree(Octree* node){
	
	if(node == NULL) return;

	float bbSize = node->getBoundingBoxSize();
	bbSize /= 2.0;
	float centerx, centery, centerz;
	node->getBoundingBoxCenter(centerx, centery, centerz);

	if (!frustum.cubeInFrustum(centerx, centery, centerz, bbSize)){
		return;
	}	

	if(node->isLeafNode()){
			
		if(!node->isVertices()) return;

		int numTris = node->getNumTriangles();

         // Set pointers.
         glEnableClientState(GL_VERTEX_ARRAY);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);


         node->vert.bind();
         glVertexPointer(3, GL_FLOAT, 0, NULL);
         node->texcoord1.bind();
         glTexCoordPointer(2, GL_FLOAT, 0, NULL);
         
         glClientActiveTextureARB(GL_TEXTURE1_ARB);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         node->texcoord2.bind();
         glTexCoordPointer(2, GL_FLOAT, 0, NULL);
         
         glClientActiveTextureARB(GL_TEXTURE0_ARB);

         glClientActiveTextureARB(GL_TEXTURE2_ARB);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         node->texcoord2.bind();
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);



         glDrawArrays(GL_TRIANGLES, 0, numTris * 3);
         node->vert.unbind();

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
         Octree **subNodes = node->getSubNodes();
         drawOctree(subNodes[TOP_FRONT_LEFT]);
         drawOctree(subNodes[TOP_FRONT_RIGHT]);
         drawOctree(subNodes[TOP_BACK_LEFT]);
         drawOctree(subNodes[TOP_BACK_RIGHT]);

         drawOctree(subNodes[BOTTOM_FRONT_LEFT]);
         drawOctree(subNodes[BOTTOM_FRONT_RIGHT]);
         drawOctree(subNodes[BOTTOM_BACK_LEFT]);
         drawOctree(subNodes[BOTTOM_BACK_RIGHT]);
    }
}
