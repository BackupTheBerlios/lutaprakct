#ifndef _TGAIMAGE_H_
#define _TGAIMAGE_H_

#include <cstdlib>

#include "image.h"

/* TODO implementar metodo write
 */

class tgaimage : public image{
	
public:

	tgaimage(){ imagedata = NULL; type = TGA; };
	tgaimage(const char *filename){ imagedata = NULL; type = TGA; load(filename); };
	~tgaimage(){ if (imagedata){ delete imagedata; imagedata = NULL; }};
	
	bool load(const char* filename, int loadingflags = 0);
	bool write(const char* filename, short int width, short int height, unsigned char depth,
						unsigned char* data);
	
private:
	bool processHeader();
	bool loadRaw();
	void BGRtoRGB();
	char encode;
	
};

#endif //_TGAIMAGE_H_
