
#include "Video.h"

#include "../util/glhelper/glextensions.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

Video::Video(){
};

Video::~Video(){
}

bool Video::initialize(VideoConfig& config ){

	this->flags = config.flags;

	height = config.height;
	width = config.width;
	fovy = config.fovy;
	znear = config.znear;
	zfar = config.zfar;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0){
		std::cout << "ERRO: Nao foi possivel inicializar o SDL!" << std::endl;
		return false;
	}
 
	atexit(SDL_Quit);
	int sdlflags;

	if (flags &SWSURFACE)
		sdlflags = SDL_SWSURFACE;
	else if (flags &HWSURFACE) 
		sdlflags = SDL_HWSURFACE;
 
	if (flags &ASYNCBLIT)
		sdlflags |= SDL_ASYNCBLIT;
	if (flags &ANYFORMAT)
		sdlflags |= SDL_ANYFORMAT;
	if (flags &HWPALETTE)
		sdlflags |= SDL_HWPALETTE;
	if (flags &DOUBLEBUF){
		if (flags &HWSURFACE)
			sdlflags |= SDL_DOUBLEBUF;
	}
	if (flags &FULLSCREEN)
		sdlflags |= SDL_FULLSCREEN;
	if (flags &OPENGL){
		SDL_GL_SetAttribute( SDL_GL_RED_SIZE     , config.redBits );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE   , config.greenBits );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE    , config.blueBits );
		SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE   , config.alphaBits  );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE   , config.depthBits );
		SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE , config.stencilBits  );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER , 1  );
		sdlflags = SDL_OPENGL;
		std::cout << "Flags do OpenGL/SDL inicializados!" << std::endl;
	}
	if (flags &OPENGLBLIT)
		sdlflags |= SDL_OPENGLBLIT;
	if (flags &RESIZABLE)
		sdlflags |= SDL_RESIZABLE;
	if (flags &NOFRAME)
		sdlflags |= SDL_NOFRAME;

	if (flags &BPP_8)
		bpp = 8;
	else if (flags &BPP_16)
		bpp = 16;
	else if (flags &BPP_24)
		bpp = 24;
	
	clearcolor[0] = config.clearColor[0];
	clearcolor[1] = config.clearColor[1];
	clearcolor[2] = config.clearColor[2];
	clearcolor[3] = config.clearColor[3];
	
	std::cout << "Inicializando SDL video..." ;
	const SDL_VideoInfo* videoinfo;
	videoinfo = SDL_GetVideoInfo();
	if (videoinfo == NULL){
		return false;
	}
	screen = SDL_SetVideoMode(width, height, videoinfo->vfmt->BitsPerPixel, sdlflags);
	std::cout << "   Pronto!" << std::endl;
	
	if (flags &OPENGL){
		initializeOpenGl();
		//inicializa as opengl extensions
		int i = 0;
		while(i < config.glExtensions.size()){
			if (haveExtension(config.glExtensions[i].c_str())){
				std::cout << "Inicializando extension: " << config.glExtensions[i] << std::endl;
				initializeExtension(config.glExtensions[i].c_str());
			}else
				std::cout << "OpenGL extension not found: " << config.glExtensions[i] << std::endl;			
			i++;
		}
	}
	
	setWindowTitle(config.windowTitle.c_str());
	showCursor(config.showCursor);
	if (screen == NULL){
		std::cout << "ERRO: Nao foi possivel inicializar o video." << std::endl;
		return false;
	}
	return true;
}

void Video::initializeOpenGl(){

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
	
}

void Video::setWindowTitle(const char* title){
	SDL_WM_SetCaption(title, title);
}

void Video::lock(){
	if (flags &OPENGL){
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}else{
		if (SDL_MUSTLOCK(screen)) 
    		SDL_LockSurface(screen); 
	}
}

void Video::unlock(){
	
	if (flags &OPENGL){
		SDL_GL_SwapBuffers();
	}else{
		if (SDL_MUSTLOCK(screen)) 
			SDL_UnlockSurface(screen);
		SDL_Flip(screen);
	}
}

int Video::getWidth(){
 return width;
}

int Video::getHeight(){
 return height;
}

float Video::getFovy(){
 return fovy;
}

float Video::getZnear(){
 return znear;
}

float Video::getZfar(){
 return zfar;
}

void Video::showCursor(bool value){
	if (value)
		SDL_ShowCursor(1);
	else
		SDL_ShowCursor(0);
}

