#ifndef _VIDEOSYSTEM_H_
#define _VIDEOSYSTEM_H_

#include "../../util/interfaces/system.h"
#include <SDL/SDL.h>

/**interface padrao para todos os tipos de video
 */

class videoSystem : public systemInterface{
	
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
	
 enum{
 	VIDEO_SDL = 1
 };
	
 videoSystem(){};
 virtual ~videoSystem(){};
 
 virtual bool initialize(int flags)=0;
 virtual void setWindowTitle(char* title)=0;
 virtual void lock()=0;
 virtual void unlock()=0;
 
 virtual int getWidth()=0;
 virtual int getHeight()=0;
 
 virtual void showCursor(bool value)=0;
 
protected:
   int videoType;
	
};

#endif //_VIDEOSYSTEM_H_
