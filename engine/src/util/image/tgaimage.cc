
#include "tgaimage.h"
#include <iostream>
#include <fstream>

#include <SDL/SDL.h>

/* o header do tga sao 12 fields, cada um sao:
# id (unsigned char)
# colour map type (unsigned char)
# image type (unsigned char)
# colour map first entry (short int)
# colour map length (short int)
# map entry size (short int)
# horizontal origin (short int)
# vertical origin (short int)
# width (short int)
# height (short int)
# pixel depth (unsigned char)
# image descriptor (unsigned char)
 */

bool tgaimage::processHeader(){
	
	short ColMapStart,ColMapLen;
	short x1,y1,x2,y2;


	if(imagedata[1] > 1){    // 0 (RGB) and 1 (Indexed) are the only types we know about
		std::cout << "imagedata[1] > 1 " << std::endl;
		return false;
	}

	encode = imagedata[2];     // Encoding flag  1 = Raw indexed image
                      //                2 = Raw RGB
                      //                3 = Raw greyscale
                      //                9 = RLE indexed
                      //               10 = RLE RGB
                      //               11 = RLE greyscale
                      //               32 & 33 Other compression, indexed

	if(encode > 11)  {
		std::cout << "encode > 11 " << std::endl;
		return false;
	}


  memcpy(&ColMapStart,&imagedata[3], 2);
  memcpy(&ColMapLen,&imagedata[5], 2);

  // Reject indexed images if not a VGA palette (256 entries with 24 bits per entry)
	//if(imagedata[1]==1){ // Indexed{
	//	if(ColMapStart!=0 || ColMapLen!=256 || imagedata[7]!=24)
			//return false;
   // }

	memcpy(&x1, &imagedata[8],2);
	memcpy(&y1, &imagedata[10],2);
	memcpy(&x2, &imagedata[12],2);
	memcpy(&y2, &imagedata[14],2);

	width=(x2-x1);
	height=(y2-y1);

	if(width < 1 || height < 1){
		std::cout << "width or height < 1" << std::endl;
		return false;
	}

	bpp = imagedata[16];

  // Check flip / interleave byte
	if(imagedata[17] > 32){ // Interleaved data
		std::cout << "interleaved data" << std::endl;
		return false;
	}

	imagesize=(width * height * (bpp/8));

	return true;
}

bool tgaimage::load(const char *filename, int loadingflags){

	std::ifstream fin;
	unsigned long filesize;

	if (imagedata)
		delete [] imagedata;
	
	fin.open(filename, std::ios::binary);
    
	if(fin == NULL){
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

		//raw indexed
		case 1:
			if((imagesize + 18 + imagedata[0])>filesize){
				std::cout << "invalid file size" << std::endl;
				return false;
			}
			
			if(imagedata[1] != 1){
				std::cout << "invalid header" << std::endl;
				return false;
			}

			if (!loadRaw()){
				std::cout << "cant load image" << std::endl;
				return false;
			}
			
			if (!loadPalette())
				return false;

		case 2: // Raw RGB
   		
			if((imagesize + 18 + imagedata[0]) > filesize){
				std::cout << "invalid file size" << std::endl;
				return false;
			}
			
			if(imagedata[1] != 0){
				std::cout << "invalid header" << std::endl;
				return false;
			}

			if (!loadRaw()){
				std::cout << "cant load image" << std::endl;
				return false;
			}

			BGRtoRGB(); 
       		break;
      
      case 3:
      		std::cout << "carregando imagem" << std::endl;
 			if (!loadRaw()){
				std::cout << "cant load image" << std::endl;
				return false;
			}
			std::cout << "pronto" << std::endl;
			break;     
      		

		default:
			std::cout << "tga invalido " << (int) encode << std::endl;
			return false;
    }

//   if((imagedata[17] & 0x20)==0) 
//     FlipImg();

	return true;
	
}

bool tgaimage::loadRaw(){
	short offset;
    unsigned char *auxdata;
 
//	if(imagedata) // Clear old data if present
//		delete [] imagedata;

	auxdata = new unsigned char[imagesize];

	if(auxdata == NULL)
		return false;

	offset = imagedata[0] + 18; // Add header to ident field size

	if(imagedata[1] == 1) // Indexed images
		offset += 768;  // Add palette offset

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

	pixelsize = bpp/8;
	
	for(index = 0; index != numPixels; index++){
		
		temp = *current;      // Get Blue value
		*current = *(current + 2);  // Swap red value into first position
		*(current + 2) = temp;  // Write back blue to last position

		current += pixelsize; // Jump to next pixel
	}
	
}

bool tgaimage::write(const char* filename, short int width, short int height, unsigned char depth,
						unsigned char* data){
	
							
	unsigned char cGarbage = 0, type, mode;
	short int iGarbage = 0;
	int i;
	FILE *file;

	file = fopen(filename, "wb");
	if (file == NULL) {
		return false;
	}

	// verifica se eh RGB/RGBA ou gayscale 
	mode = depth / 8;
	if ((depth == 24) || (depth == 32))
		type = 2;
	else
		type = 3;

	fwrite(&cGarbage, sizeof(unsigned char), 1, file);
	fwrite(&cGarbage, sizeof(unsigned char), 1, file);

	fwrite(&type, sizeof(unsigned char), 1, file);

	fwrite(&iGarbage, sizeof(short int), 1, file);
	fwrite(&iGarbage, sizeof(short int), 1, file);
	fwrite(&cGarbage, sizeof(unsigned char), 1, file);
	fwrite(&iGarbage, sizeof(short int), 1, file);
	fwrite(&iGarbage, sizeof(short int), 1, file);

	fwrite(&width, sizeof(short int), 1, file);
	fwrite(&height, sizeof(short int), 1, file);
	fwrite(&depth, sizeof(unsigned char), 1, file);

	fwrite(&cGarbage, sizeof(unsigned char), 1, file);
	// swap nos pixels do tga
	unsigned char aux;
	if (mode >= 3){
		for (i=0; i < width * height * mode; i+= mode) {
			aux = data[i];
			data[i] = data[i+2];
			data[i+2] = aux;
		}
	}

	// salva a imagem toda
	fwrite(data, sizeof(unsigned char), width * height * mode, file);
	fclose(file);
	return true;
}

bool tgaimage::loadPalette(){

	unsigned char bTemp;
	short iIndex,iPalPtr;
  
   // Delete old palette if present
	if(palette){
		delete [] palette;
		palette = NULL;
	}
 
  // Create space for new palette
	palette = new unsigned char[768];
 
	if(palette == NULL)
		return false;
 
  // VGA palette is the 768 bytes following the header
	memcpy(palette, &imagedata[imagedata[0]+18], 768);
 
  // Palette entries are BGR ordered so we have to convert to RGB
	for(iIndex = 0,iPalPtr = 0; iIndex != 256; ++iIndex, iPalPtr += 3){
		bTemp = palette[iPalPtr];               // Get Blue value
		palette[iPalPtr] = palette[iPalPtr+2]; // Copy Red to Blue
		palette[iPalPtr+2] = bTemp;             // Replace Blue at the end
	}
	
}

