#ifndef __CSPRITEBASE_H__
#define __CSPRITEBASE_H__

#include <SDL/SDL.h>

/**
*frame de cada sprite, guarda o tempo de frame e a imagem do frame
*/
struct spriteFrame{
  SDL_Surface *image;
  int pause; //tempo em milissegundos
};

class spriteBase{
  public:
  int initialize(char *filename);

  spriteFrame *anim;
  int built, numframes, w, h;
};

#endif
