
#include "sdlvideo.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

sdlVideo::sdlVideo(){
	videoType = VIDEO_SDL;
};

bool sdlVideo::initialize(int flags){

 this->flags = flags;

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
  SDL_GL_SetAttribute( SDL_GL_RED_SIZE     , 8  );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE   , 8  );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE    , 8  );
  SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE   , 8  );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE   , 24 );
  SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE , 8  );
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
	
	if (flags &RES_640x480){
		height = 480;
		width = 640;
	} else if (flags &RES_800x600){
		height = 600;
		width = 800;
	} else if (flags &RES_1024x768){
		height = 768;
		width = 1024;
	}
	if (flags &BPP_8)
		bpp = 8;
	else if (flags &BPP_16)
		bpp = 16;
	else if (flags &BPP_24)
		bpp = 24;
	
	std::cout << "Inicializando SDL video..." ;
	const SDL_VideoInfo* videoinfo;
	videoinfo = SDL_GetVideoInfo();
	if (videoinfo == NULL)
		return false;
	screen = SDL_SetVideoMode(width, height, videoinfo->vfmt->BitsPerPixel, sdlflags);
	std::cout << "   Pronto!" << std::endl;
	if (flags &OPENGL)
		initializeOpenGl();
	if (screen == NULL){
		std::cout << "ERRO: Nao foi possivel inicializar o video." << std::endl;
		return false;
	}
	return true;
}

void sdlVideo::initializeOpenGl(){

	float ratio = (float) width / (float) height;
	glEnable(GL_DEPTH_TEST); 
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	gluPerspective(75.0, ratio, 1.0, 5000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	
	glEnable(GL_CULL_FACE);
	glClearStencil(0x00);
	glPolygonOffset(1.0, 1.0);	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}

void sdlVideo::setWindowTitle(char* title){
	SDL_WM_SetCaption(title, title);
}

void sdlVideo::lock(){
	if (flags &OPENGL){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}else{
		if (SDL_MUSTLOCK(screen)) 
    		SDL_LockSurface(screen); 
	}
}

void sdlVideo::unlock(){
	
	if (flags &OPENGL){
		SDL_GL_SwapBuffers();
	}else{
		if (SDL_MUSTLOCK(screen)) 
			SDL_UnlockSurface(screen);
		SDL_Flip(screen);
	}
}

int sdlVideo::getWidth(){
 return width;
}

int sdlVideo::getHeight(){
 return height;
}

void sdlVideo::showCursor(bool value){
	if (value)
		SDL_ShowCursor(1);
	else
		SDL_ShowCursor(0);
}

