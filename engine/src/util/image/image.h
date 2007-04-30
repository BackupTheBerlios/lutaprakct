#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <cstdlib>
#include <string>
 //#include <GL/gl.h>

/* interface da image, todos os outros formatos herdam desse: jpgimage, pngimage, tgaimage, etc
 */

enum imagetype{
	JPG,
	TGA,
	PNG,
	BMP,
	PCX,
	DDS
};

class Image{
	
public:

	Image(){imagedata = NULL;};
	virtual ~Image(){};
	
	
	virtual bool load(std::string& filename, int loadingflags = 0)=0;
	virtual bool write(std::string& filename, short int width, short int height, unsigned char depth,
						unsigned char* data)=0;
	
	unsigned char* imagedata;
	
	int getWidth(){ return width; }
	int getHeight(){ return height; }
	
protected:

	int type;
	int width, height, bpp, imagesize;

	
};

//funcao de carregar imagem:

Image* loadImage(std::string& filename);

#endif //_IMAGE_H_
