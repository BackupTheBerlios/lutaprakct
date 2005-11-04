
#include "tgaimage.h"
#include <iostream>
#include <fstream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

bool tgaimage::processHeader(){
	
	short ColMapStart,ColMapLen;
	short x1,y1,x2,y2;


	if(imagedata[1] > 1)    // 0 (RGB) and 1 (Indexed) are the only types we know about
		return false;

	encode = imagedata[2];     // Encoding flag  1 = Raw indexed image
                      //                2 = Raw RGB
                      //                3 = Raw greyscale
                      //                9 = RLE indexed
                      //               10 = RLE RGB
                      //               11 = RLE greyscale
                      //               32 & 33 Other compression, indexed

std::cout << "encode " << imagedata[2] << std::endl;
	if(encode > 11)  
		return false;


  memcpy(&ColMapStart,&imagedata[3], 2);
  memcpy(&ColMapLen,&imagedata[5], 2);

  // Reject indexed images if not a VGA palette (256 entries with 24 bits per entry)
	if(imagedata[1]==1){ // Indexed{
		if(ColMapStart!=0 || ColMapLen!=256 || imagedata[7]!=24)
			return false;
    }

	memcpy(&x1, &imagedata[8],2);
	memcpy(&y1, &imagedata[10],2);
	memcpy(&x2, &imagedata[12],2);
	memcpy(&y2, &imagedata[14],2);

	width=(x2-x1);
	height=(y2-y1);

	if(width < 1 || height < 1)
		return false;

	bpp = imagedata[16];

  // Check flip / interleave byte
	if(imagedata[17] > 32) // Interleaved data
		return false;

	imagesize=(width * height * (bpp/8));

	return true;
}

bool tgaimage::load(const char *filename, int loadingflags){

	std::ifstream fin;
	unsigned long filesize;

	//if (imagedata)
		//delete [] imagedata;
	
	fin.open(filename, std::ios::binary);
    
	if(fin==NULL){
		std::cout << "no such file" << std::endl;
		return false;
	}

	fin.seekg(0, std::ios_base::end);
	filesize = fin.tellg();
	fin.seekg(0, std::ios_base::beg);


	imagedata=new unsigned char[filesize];

	if(imagedata == NULL){
		fin.close();
		std::cout << "no memory" << std::endl;
		return false;
    }

	fin.read((char*)imagedata, filesize);
	fin.close();

	if(!processHeader()){
		std::cout << "invalid header" << std::endl;
		return false;
	}

	switch(encode){

		case 2: // Raw RGB
   		{
   				std::cout << "lendo tga" << std::endl;
			if((imagesize+18+imagedata[0])>filesize){
				std::cout << "invalid file size" << std::endl;
				return false;
			}
			
			if(imagedata[1]!=0){
				std::cout << "invalid header" << std::endl;
				return false;
			}

			if (!loadRaw()){
				std::cout << "cant load image" << std::endl;
				return false;
			}

			BGRtoRGB(); 
       break;
      }

		default:
			std::cout << "sei nao " << encode << std::endl;
			return false;
    }

//   if((imagedata[17] & 0x20)==0) 
//     FlipImg();


 /*  std::cout << "etste" << std::endl;
	SDL_Surface *img = (SDL_Surface*) IMG_Load(filename);
	imagedata = (GLubyte*) img->pixels;
	SDL_SaveBMP( img, "lol.bmp");
	   if ( !imagedata )
   {
      std::cout << "IMG_Load: " << IMG_GetError() << std::endl;
   }
	width = img->w;
	height = img->h;
	//bpp = img->bpp;
*/
	return true;
	
}

bool tgaimage::loadRaw(){
	short offset;
    unsigned char *auxdata;
 
//	if(imagedata) // Clear old data if present
//		delete [] imagedata;

	auxdata=new unsigned char[imagesize];

	if(auxdata==NULL)
		return false;

	offset=imagedata[0]+18; // Add header to ident field size

	if(imagedata[1] == 1) // Indexed images
		offset+= 768;  // Add palette offset

	memcpy(auxdata, &imagedata[offset], imagesize);
//	delete imagedata;
	imagedata = auxdata;
	return true;
	
}

void tgaimage::BGRtoRGB(){

	unsigned long index, numPixels;
	unsigned char *current;
	unsigned char temp;
	short pixelsize;

	current = imagedata;

	numPixels = width*height;

	pixelsize=bpp/8;

	for(index=0; index!=numPixels; index++){
		temp = *current;      // Get Blue value
		*current =* (current+2);  // Swap red value into first position
		*(current+2) = temp;  // Write back blue to last position

		current += pixelsize; // Jump to next pixel
	}
	
}

bool tgaimage::write(char* filename){
	return false;
}



/*	GLubyte TGAheader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	GLubyte TGAcmp[12];
	GLubyte header[6];
	GLuint imagesize, temp, bytesPerPixel;
std::cout << "lendo tga" << std::endl;
	FILE *f = fopen (filename, "rb");
	
	if ((f == NULL)
	    || (fread (TGAcmp, 1, sizeof (TGAcmp), f) != sizeof (TGAcmp))
	    || (memcmp (TGAheader, TGAcmp, sizeof (TGAheader)) != 0)
	    || (fread (header, 1, sizeof (header), f) != sizeof (header))){
		fclose (f);
		std::cout << "nao foi possivel ler a textura" << std::endl;
		return false;
	}
	width = header[1] * 256 + header[0];
	height = header[3] * 256 + header[2];
	std::cout << "tamanho " <<width << std::endl;
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
	*/
