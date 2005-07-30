
#ifndef _VIDEOSYSTEM_H_
#define _VIDEOSYSTEM_H_

#include <SDL/SDL.h>

#include "../../util/singleton.h"

/** Essa classe Ã© responsÃ¡vel por inicializar o
  * video e o SDL. Tudo relacionado com o gerenciamento
  * da janela Ã© feito aqui.
*/  

class videosystem{

public:
 enum{
  SWSURFACE    = 1 << 1,
  HWSURFACE    = 1 << 2,
  ASYNCBLIT    = 1 << 3,
  ANYFORMAT    = 1 << 4,
  HWPALETTE    = 1 << 5,
  DOUBLEBUF    = 1 << 6,
  FULLSCREEN   = 1 << 7,
  OPENGL       = 1 << 8,
  OPENGLBLIT   = 1 << 9,
  RESIZABLE    = 1 << 10,
  NOFRAME      = 1 << 11,
  
  RES_640x480  = 1 << 12,
  RES_800x600  = 1 << 13,
  RES_1024x768 = 1 << 14,
  
  BPP_8        = 1 << 15,
  BPP_16       = 1 << 16,
  BPP_24       = 1 << 17
 };
 

 bool initialize(int flags);
 void shutdown();
 void setWindowTitle(char* title);
 void lock();
 void unlock();

 void draw();
 
 SDL_Surface* getScreen();
 int getWidth();
 int getHeight();
private:
 SDL_Surface *screen;
 int height, width, bpp;
};

typedef singleton<videosystem> VideoSystem;

#endif
