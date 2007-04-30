
#include "sdlvideo.h"
#include "../../../../util/glhelper/glextensions.h"
#include "../../../../../libs/tinyxml/tinyxml.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

SdlVideo::SdlVideo(){
	videoType = VIDEO_SDL;
};

bool SdlVideo::initialize(int flags){

	this->flags = flags;

	TiXmlDocument configdoc("config.xml");
	if (!configdoc.LoadFile()){
		std::cout << "(SdlVideo)ERRO: Arquivo de configuracao config.xml nao encontrado." << std::endl;
		configdoc.Clear();
		return false;
	}

	TiXmlElement* elem = configdoc.FirstChildElement("engine");
	TiXmlElement* openglcfg = elem->FirstChildElement("opengl");
	if (!openglcfg){
		std::cout << "ERRO: config.xml sem tag opengl." << std::endl;
		configdoc.Clear();
		return false;
	}
	TiXmlElement* viewportcfg = openglcfg->FirstChildElement("viewport");
	height = atoi(viewportcfg->Attribute("height"));
	width = atoi(viewportcfg->Attribute("width"));
	fovy = atof(viewportcfg->Attribute("fovy"));
	znear = atof(viewportcfg->Attribute("znear"));
	zfar = atof(viewportcfg->Attribute("zfar"));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0){
		std::cout << "ERRO: Nao foi possivel inicializar o SDL!" << std::endl;
		configdoc.Clear();
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
		TiXmlElement* bufferscfg = openglcfg->FirstChildElement("buffers");
		SDL_GL_SetAttribute( SDL_GL_RED_SIZE     , atoi(bufferscfg->Attribute("redsize"))  );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE   , atoi(bufferscfg->Attribute("greensize"))  );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE    , atoi(bufferscfg->Attribute("bluesize"))  );
		SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE   , atoi(bufferscfg->Attribute("alphasize"))  );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE   , atoi(bufferscfg->Attribute("depthsize")) );
		SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE , atoi(bufferscfg->Attribute("stencilsize"))  );
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
	
	TiXmlElement* clearcolorcfg = openglcfg->FirstChildElement("clearcolor");
	clearcolor[0] = atof(clearcolorcfg->Attribute("r"));
	clearcolor[1] = atof(clearcolorcfg->Attribute("g"));
	clearcolor[2] = atof(clearcolorcfg->Attribute("b"));
	clearcolor[3] = atof(clearcolorcfg->Attribute("a"));
	
	std::cout << "Inicializando SDL video..." ;
	const SDL_VideoInfo* videoinfo;
	videoinfo = SDL_GetVideoInfo();
	if (videoinfo == NULL){
		configdoc.Clear();
		return false;
	}
	screen = SDL_SetVideoMode(width, height, videoinfo->vfmt->BitsPerPixel, sdlflags);
	std::cout << "   Pronto!" << std::endl;
	
	if (flags &OPENGL){
		initializeOpenGl();
		//inicializa as opengl extensions
		TiXmlElement* extension = openglcfg->FirstChildElement("extension");
		while(extension){
			if (haveExtension(extension->Attribute("name"))){
				std::cout << "Inicializando extension: " << extension->Attribute("name") << std::endl;
				initializeExtension(extension->Attribute("name"));
			}else
				std::cout << "OpenGL extension not found: " << extension->Attribute("name") << std::endl;			
			extension = extension->NextSiblingElement("extension");
		}
	}
	
	TiXmlElement* windowcfg = elem->FirstChildElement("window");
	if (windowcfg){
		setWindowTitle(windowcfg->Attribute("title"));
		bool value;
		if (  atoi(windowcfg->Attribute("showcursor"))  == 1 )
			value = true;
		else
			value = false;
		showCursor(value);
	}
	configdoc.Clear();
	if (screen == NULL){
		std::cout << "ERRO: Nao foi possivel inicializar o video." << std::endl;
		return false;
	}
	return true;
}

void SdlVideo::initializeOpenGl(){

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

void SdlVideo::setWindowTitle(const char* title){
	SDL_WM_SetCaption(title, title);
}

void SdlVideo::lock(){
	if (flags &OPENGL){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}else{
		if (SDL_MUSTLOCK(screen)) 
    		SDL_LockSurface(screen); 
	}
}

void SdlVideo::unlock(){
	
	if (flags &OPENGL){
		SDL_GL_SwapBuffers();
	}else{
		if (SDL_MUSTLOCK(screen)) 
			SDL_UnlockSurface(screen);
		SDL_Flip(screen);
	}
}

int SdlVideo::getWidth(){
 return width;
}

int SdlVideo::getHeight(){
 return height;
}

void SdlVideo::showCursor(bool value){
	if (value)
		SDL_ShowCursor(1);
	else
		SDL_ShowCursor(0);
}

