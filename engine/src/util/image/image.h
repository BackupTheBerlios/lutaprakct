#ifndef _IMAGE_H_
#define _IMAGE_H_

 #include <GL/gl.h>

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

class image{
	
public:

	image(){};
	virtual ~image(){};
	
	
	virtual bool load(const char* filename, int loadingflags = 0)=0;
	virtual bool write(char* filename)=0;
	
	GLubyte *imagedata;
	
	int getWidth(){ return width; }
	int getHeight(){ return height; }
	
protected:

	int type;
	int width, height, bpp, imagesize;

	
};

//funcao de carregar imagem:

image* loadImage(const char* filename);

#endif //_IMAGE_H_
