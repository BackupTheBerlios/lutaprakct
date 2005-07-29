#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include <SDL/SDL.h>

#include "spritebase.h"

class sprite
{
  public:
  sprite() {};
  ~sprite() {};
  int initialize(spriteBase *base, SDL_Surface *screen);
  void draw();
  void clearBG();
  void updateBG();

  void setFrame(int nr) { frame = nr; }
  int getFrame() { return frame; }

  void setSpeed(float nr) { speed = nr; }
  float getSpeed() { return speed; }

  void toggleAnim() { animating = !animating; }
  void startAnim() { animating = 1; }
  void stopAnim() { animating = 0; }
  void rewind() { frame = 0; }

  void xadd(int nr) { x+=nr; }
  void yadd(int nr) { y+=nr; }
  void xset(int nr) { x=nr; }
  void yset(int nr) { y=nr; }
  void set(int xx, int yy) { x=xx; y=yy; }

  private:
  int frame;
  int x, y, oldX, oldY;
  int animating;
  int drawn;
  float speed;
  long lastupdate;
  spriteBase *basesprite;
  SDL_Surface *backreplacement;
  SDL_Surface *screen;
};

#endif
