#ifndef _VIDEOSYSTEM_H_
#define _VIDEOSYSTEM_H_

#include <SDL/SDL.h>

/**interface padrao para todos os tipos de video
 */

class VideoSystem  {
	
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
	
 enum{
 	VIDEO_SDL = 1
 };
	
 VideoSystem(){};
 virtual ~VideoSystem(){};
 
 virtual bool initialize(int flags)=0;
 virtual void setWindowTitle(const char* title)=0;
 virtual void lock()=0;
 virtual void unlock()=0;
 
 virtual int getWidth()=0;
 virtual int getHeight()=0;
 
 virtual void showCursor(bool value)=0;
 
protected:
   int videoType;
	
};

VideoSystem* initializeVideo(int videoType);

#endif //_VIDEOSYSTEM_H_
