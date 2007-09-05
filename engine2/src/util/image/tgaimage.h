#ifndef _TGAIMAGE_H_
#define _TGAIMAGE_H_

#include <cstdlib>

#include "image.h"

/* TODO implementar metodo write
 */

class TgaImage : public Image{
	
public:

	TgaImage(){ imagedata = NULL; type = TGA; palette = NULL; };
	TgaImage(std::string& filename){ imagedata = NULL; palette = NULL; type = TGA; load(filename); };
	~TgaImage(){ 
		if (imagedata){ 
			delete imagedata; 
			imagedata = NULL;
		}
		if (palette){
			delete palette; 
			palette = NULL;
		} 
	};
	
	bool load(std::string& filename, int loadingflags = 0);
	bool loadPalette();
	bool write(std::string& filename, short int width, short int height, unsigned char depth,
						unsigned char* data);
	
private:
	bool processHeader();
	bool loadRaw();
	void BGRtoRGB();
	char encode;
	unsigned char* palette;
};

#endif //_TGAIMAGE_H_
