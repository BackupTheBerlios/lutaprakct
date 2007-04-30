#ifndef _SDLVIDEO_H_
#define _SDLVIDEO_H_

#include <SDL/SDL.h>


#include "../videosystem.h"

/** Essa classe eh responsavel por inicializar o
  * video , o SDL e o OpenGL. Tudo relacionado com o gerenciamento
  * da janela sao feito aqui.
*/  

class SdlVideo : public VideoSystem{

public:

	SdlVideo();
	~SdlVideo(){};

	bool initialize(int flags);
	void shutdown();
	void setWindowTitle(const char* title);
	void lock();
	void unlock();
 
	int getWidth();
	int getHeight();
	
	void showCursor(bool value);
private:
	void initializeOpenGl();
 
	SDL_Surface *screen;
	int height, width, bpp, flags;
	float clearcolor[4];
	
	float fovy, znear, zfar;
};

#endif //_VIDEOSYSTEM_H_
