#include "sprite.h"

int sprite::initialize(spriteBase *base, SDL_Surface *screen)
{
  basesprite = base;
  if(basesprite->built)
  {
    if(basesprite->numframes>1) animating=1;
    backreplacement = SDL_DisplayFormat(basesprite->anim[0].image);
  }
  screen = screen;
  return 0;
}

void sprite::clearBG()
{
  if(drawn==1)
  {
    SDL_Rect dest;
    dest.x = oldX;
    dest.y = oldY;
    dest.w = basesprite->w;
    dest.h = basesprite->h;
    SDL_BlitSurface(backreplacement, NULL, screen, &dest);
  }
}

void sprite::updateBG()
{
  SDL_Rect srcrect;
  srcrect.w = basesprite->w;
  srcrect.h = basesprite->h;
  srcrect.x = x;
  srcrect.y = y;
  oldX=x;
  oldY=y;
  SDL_BlitSurface(screen, &srcrect, backreplacement, NULL);
}

void sprite::draw()
{
  if(animating == 1)
  {
    if(lastupdate+basesprite->anim[frame].pause*speed<SDL_GetTicks())
    {
      frame++;
      if(frame>basesprite->numframes-1) frame=0;
      lastupdate = SDL_GetTicks();
    }
  }

  if(drawn==0) drawn=1;

  SDL_Rect dest;
  dest.x = x; 
  dest.y = y;
  SDL_BlitSurface(basesprite->anim[frame].image, NULL, screen, &dest);
}
