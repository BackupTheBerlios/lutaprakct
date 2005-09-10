#ifndef _TGAIMAGE_H_
#define _TGAIMAGE_H_

#include <cstdlib>

#include "image.h"

/* TODO implementar metodo write
 */

class tgaimage : public image{
	
public:

	tgaimage(const char *filename){ imagedata = NULL; type = TGA; load(filename); };
	~tgaimage(){};
	
	bool load(const char* filename, int loadingflags = 0);
	bool write(char* filename);
	
};

#endif //_TGAIMAGE_H_
