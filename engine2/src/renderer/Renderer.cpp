#include <list>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <iostream>
#include <float.h>
#include "Renderer.h"
#include "QuatCamera.h"
#include "../util/DataManager.h"
#include "../entities/StaticEntity.h"

#include "../lights/ShLight.h"


Renderer::Renderer(){
	screenShotNumber = 0;
}

Renderer::~Renderer(){
}

void Renderer::handleEvent(const event& e){
	switch (e.type){
		case E_KEY_F1:{
				//unsigned char idteste = '1';
				int viewport[4];
				glGetIntegerv(GL_VIEWPORT, viewport);
				unsigned char* data = NULL;
				data =  new unsigned char[3 * viewport[2] * viewport[3]];
				glPixelStorei(GL_PACK_ALIGNMENT,1);
				glReadBuffer(GL_FRONT);
				glReadPixels(0,0, viewport[2], viewport[3], GL_RGB, GL_UNSIGNED_BYTE, data);
			//	TgaImage img;
				char filename[50];
				if (screenShotNumber < 10)
					sprintf(filename, "img_00%d.tga", screenShotNumber );
				else if (screenShotNumber <= 99 )
					sprintf(filename, "img_0%d.tga", screenShotNumber );
				else
					sprintf(filename, "img_%d.tga", screenShotNumber );
				std::string file(filename);
				//img.write(file, viewport[2], viewport[3], 24, data);
				screenShotNumber++;
				
				delete data;
			break;
		}
	}
}

unsigned int vbid, vbib;

bool Renderer::initialize(VideoConfig& config){
	//if (!light.initialize(1))
	//	std::cout << "nao luz" << std::endl;
	//if (!shadows.initialize())
	//	std::cout << "Sombras nao foram inicializadas." << std::endl;
		
	//duck = new StaticEntity;
	//if (duck->initialize("duck_triangulate_deindexer.dae") == false)
	//	std::cout << "duck_triangulate_deindexer.dae not found." << std::endl;
	initializeSdl(config);
	initializeOpenGl();
	
	return true;
}

void Renderer::stop(){
}

void Renderer::update(){
	beginDraw();
	draw();
	endDraw();
}

void Renderer::draw(){
}

void Renderer::setupViewMatrix(){
	QUATCAMERA::getInstance().setupViewMatrix();
}

void Renderer::setupProjectionMatrix(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const float fAspect = (float)width / (float) height;
	gluPerspective(fovy, fAspect, znear, zfar);
}

void Renderer::beginDraw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setupProjectionMatrix();
	setupViewMatrix();
}

void Renderer::endDraw(){
	SDL_GL_SwapBuffers();
}


int Renderer::initializeSdl(VideoConfig& config){

	this->flags = config.flags;

	height = config.height;
	width = config.width;
	fovy = config.fovy;
	znear = config.znear;
	zfar = config.zfar;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0){
		std::cout << "ERRO: Nao foi possivel inicializar o SDL!" << std::endl;
		return -1;
	}
 
	atexit(SDL_Quit);
	int sdlflags;

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE     , config.redBits );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE   , config.greenBits );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE    , config.blueBits );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE   , config.alphaBits  );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE   , config.depthBits );
	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE , config.stencilBits  );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER , 1  );
	sdlflags = SDL_OPENGL;

	if (flags &FULLSCREEN)
		sdlflags |= SDL_FULLSCREEN;
	if (flags &RESIZABLE)
		sdlflags |= SDL_RESIZABLE;
	if (flags &NOFRAME)
		sdlflags |= SDL_NOFRAME;

	bpp = config.bpp;
	
	clearcolor[0] = config.clearColor[0];
	clearcolor[1] = config.clearColor[1];
	clearcolor[2] = config.clearColor[2];
	clearcolor[3] = config.clearColor[3];
	
	std::cout << "Inicializando SDL video..." ;
	const SDL_VideoInfo* videoinfo;
	videoinfo = SDL_GetVideoInfo();
	if (videoinfo == NULL){
		return -1;
	}
	screen = SDL_SetVideoMode(width, height, videoinfo->vfmt->BitsPerPixel, sdlflags);
	std::cout << "   Pronto!" << std::endl;
		
	SDL_WM_SetCaption(config.windowTitle.c_str(), config.windowTitle.c_str());
	SDL_ShowCursor(config.showCursor);
	if (screen == NULL){
		std::cout << "ERRO: Nao foi possivel inicializar o video." << std::endl;
		return -1;
	}
	return 0;

}

int Renderer::initializeOpenGl(){

	float ratio = (float) width / (float) height;
	glEnable(GL_DEPTH_TEST); 
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	gluPerspective(fovy, ratio, znear, zfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(clearcolor[0], clearcolor[1], clearcolor[2], clearcolor[3]);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	
	//glEnable(GL_CULL_FACE);
	glClearStencil(0x00);
	//glPolygonOffset(1.0, 1.0);	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	//inicializa as opengl extensions
/*	int i = 0;
	while(i < config.glExtensions.size()){
		if (haveExtension(config.glExtensions[i].c_str())){
			std::cout << "Inicializando extension: " << config.glExtensions[i] << std::endl;
			initializeExtension(config.glExtensions[i].c_str());
		}else
			std::cout << "OpenGL extension not found: " << config.glExtensions[i] << std::endl;			
		i++;
	}*/
	
	return 0;

}
