#ifndef VIDEO_H_
#define VIDEO_H_

#include <SDL/SDL.h>
#include "VideoConfig.h"
#include "../util/patterns/Singleton.h" 

class Video{
	
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
  
  BPP_8        = 1 << 15,
  BPP_16       = 1 << 16,
  BPP_24       = 1 << 17
 };


	Video();
	~Video();

	bool initialize(VideoConfig& config);
	void stop();
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
	float znear, zfar, fovy;
	
};

typedef Singleton<Video> VIDEO;

#endif /*VIDEO_H_*/
