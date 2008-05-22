#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <cstdlib>

enum imagetype{
	JPG,
	TGA,
	PNG,
	BMP,
	PCX,
	DDS
};

enum imageerrors{
	FILE_NOT_FOUND = 1,
	NO_ENOUGH_MEMORY,
	INVALID_FILE_HEADER,
	INVALID_FILE_SIZE,
	INVALID_FILE,
	INVALID_IMAGE_SIZE,
	INVALID_IMAGE_DATA,
	INVALID_ENCODING,
	INVALID_FILE_TYPE,
	INTERLEAVED_DATA
};

class Image{
	
public:

	Image(){imagedata = NULL; palette = NULL;};
	~Image(){ delete imagedata; delete palette; };
	
	
	int load(const char* filename);
	int write(char* filename, short int width, short int height, unsigned char depth,
						unsigned char* data);
	
	int getWidth(){ return width; }
	int getHeight(){ return height; }

	int loadTga(const char* filename);
	int loadRawTga();
	void BgrtoRgb();
	int writeTga( char* filename,short int width, short int height, unsigned char depth,
			unsigned char* data  );
	
	unsigned char* imagedata;
	
protected:

	int type;
	int width, height, bpp, imagesize;
	unsigned char* palette;

	
};


#endif //_IMAGE_H_
