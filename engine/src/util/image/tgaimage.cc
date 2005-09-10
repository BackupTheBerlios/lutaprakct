
#include "tgaimage.h"
#include <iostream>

bool tgaimage::load(const char *filename, int loadingflags){

	GLubyte TGAheader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	GLubyte TGAcmp[12];
	GLubyte header[6];
	GLuint imagesize, temp, bytesPerPixel;

	FILE *f = fopen (filename, "rb");
	if ((f == NULL)
	    || (fread (TGAcmp, 1, sizeof (TGAcmp), f) != sizeof (TGAcmp))
	    || (memcmp (TGAheader, TGAcmp, sizeof (TGAheader)) != 0)
	    || (fread (header, 1, sizeof (header), f) != sizeof (header))){
		fclose (f);
		return false;
	}
	width = header[1] * 256 + header[0];
	height = header[3] * 256 + header[2];
	bpp = header[4];
	bytesPerPixel = bpp / 8;
	imagesize = width * height * bytesPerPixel;

	if ((width <= 0) || (height <= 0)
	    || ((header[4] != 24) && (header[4] != 32))){
		fclose (f);
		return false;
	}

	imagedata = new GLubyte[imagesize];
	if ((imagedata == NULL)
	    || (fread (imagedata, 1, imagesize, f) != imagesize)){
		delete imagedata;
		fclose (f);
		return false;
	}
	//swap no formato BGR do TGA pra RGB somente se
	//nao for especificado o formato BGR ou BGRA
//	if ( (format != GL_BGR_EXT) && (format != GL_BGRA_EXT) ){
 		for (GLuint i = 0; i < (imagesize); i += bytesPerPixel){
			temp = imagedata[i];	//guarda o valor do B
			imagedata[i] = imagedata[i + 2];	//B recebe o valor do R
			imagedata[i + 2] = temp;	//R recebe o valor de B, ficando RGB
		}
//	}
	fclose (f);
	return true;
	
	
}

bool tgaimage::write(char* filename){
	return false;
}
