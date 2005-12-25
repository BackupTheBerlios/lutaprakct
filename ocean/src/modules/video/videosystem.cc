
#include "videosystem.h"
#include <iostream>

bool videosystem::initialize(int flags){

 std::cout << "inicializando video.." << std::endl;
 if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0){
  std::cout << "Nao foi possivel inicializar o SDL!" << std::endl;
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
 if (flags &OPENGL)
  sdlflags |= SDL_OPENGL;
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
	
	screen = SDL_SetVideoMode(width, height, bpp, sdlflags);
	if (screen == NULL){
		std::cout << "Nao foi possivel inicializar o video." << std::endl;
		return false;
	}
	
	std::cout << "Video inicializado com sucesso!" << std::endl;
	return true;
}

void videosystem::setWindowTitle(char* title){
	SDL_WM_SetCaption(title, title);
}

void videosystem::lock(){
	if (SDL_MUSTLOCK(screen)) 
    	SDL_LockSurface(screen); 
}

void videosystem::unlock(){
  if (SDL_MUSTLOCK(screen)) 
    SDL_UnlockSurface(screen);
  SDL_Flip(screen);
}

SDL_Surface* videosystem::getScreen(){
	return screen;
}

int videosystem::getWidth(){
 return width;
}

int videosystem::getHeight(){
 return height;
}

void videosystem::draw(){

}
