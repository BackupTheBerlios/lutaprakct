#ifndef _SDLVIDEO_H_
#define _SDLVIDEO_H_

#include <SDL/SDL.h>


#include "../videosystem.h"

/** Essa classe eh responsavel por inicializar o
  * video , o SDL e o OpenGL. Tudo relacionado com o gerenciamento
  * da janela sao feito aqui.
*/  

class sdlVideo : public videoSystem{

public:

	sdlVideo();
	~sdlVideo(){};

	bool initialize(int flags);
	void shutdown();
	void setWindowTitle(char* title);
	void lock();
	void unlock();
 
	int getWidth();
	int getHeight();
	
	void showCursor(bool value);
private:
	void initializeOpenGl();
 
	SDL_Surface *screen;
	int height, width, bpp, flags;
};

#endif //_VIDEOSYSTEM_H_
