
#include <cstring>
#include "Image.h"
#include <fstream>

int Image::load(char* filename){

	char* aux = strchr (filename, '.');
	aux++;
	int ret = 0;
	if ((strcmp (aux, "TGA") == 0) || (strcmp (aux, "tga") == 0)){
        ret = loadTga(filename);
        return ret;
	}
	return INVALID_FILE_TYPE;
}

int Image::write(char* filename, short int width, short int height, unsigned char depth,
		unsigned char* data){
	
	char* aux = strchr (filename, '.');
	aux++;
	int ret = 0;
	if ((strcmp (aux, "TGA") == 0) || (strcmp (aux, "tga") == 0)){
        ret = writeTga(filename, width, height, depth, data);
        return ret;
	}
	return INVALID_FILE_TYPE;	
	
}

//TODO usar file com C e nao com c++
int Image::loadTga(char* filename) {

	std::ifstream fin;
	unsigned long filesize;
	char encode;
	
	if (imagedata)
		delete [] imagedata;
	
	fin.open(filename, std::ios::binary);
    
	if(fin == NULL){
		return FILE_NOT_FOUND;
	}

	fin.seekg(0, std::ios_base::end);
	filesize = fin.tellg();
	fin.seekg(0, std::ios_base::beg);

	imagedata = new unsigned char[filesize];

	if(imagedata == NULL){
		fin.close();
		return NO_ENOUGH_MEMORY;
    }

	fin.read((char*)imagedata, filesize);
	fin.close();

	short ColMapStart,ColMapLen;
	short x1,y1,x2,y2;

	if(imagedata[1] > 1){    // 0 (RGB) and 1 (Indexed) are the only types we know about
		return INVALID_IMAGE_DATA;
	}

	encode = imagedata[2];     // Encoding flag  1 = Raw indexed image
                      //                2 = Raw RGB
                      //                3 = Raw greyscale
                      //                9 = RLE indexed
                      //               10 = RLE RGB
                      //               11 = RLE greyscale
                      //               32 & 33 Other compression, indexed

	if(encode > 11)  {
		INVALID_ENCODING;
		return false;
	}


	memcpy(&ColMapStart,&imagedata[3], 2);
	memcpy(&ColMapLen,&imagedata[5], 2);

	memcpy(&x1, &imagedata[8],2);
	memcpy(&y1, &imagedata[10],2);
	memcpy(&x2, &imagedata[12],2);
	memcpy(&y2, &imagedata[14],2);

	width = (x2-x1);
	height = (y2-y1);

	if(width < 1 || height < 1){
		return INVALID_IMAGE_SIZE;
	}

	bpp = imagedata[16];

	if(imagedata[17] > 32){ // Interleaved data
		return INTERLEAVED_DATA;
	}

	imagesize=(width * height * (bpp/8));

	int ret;
	switch(encode){

		//raw indexed
		case 1:
			if((imagesize + 18 + imagedata[0])>filesize){
				return INVALID_FILE_SIZE;
			}
			
			if(imagedata[1] != 1){
				return INVALID_FILE_HEADER;
			}

			ret = loadRawTga();
			if (ret > 0){
				return ret;
			}
			
			//load palette
			unsigned char bTemp;
			short iIndex,iPalPtr;
		  
			if(palette){
				delete [] palette;
				palette = NULL;
			}
		 
		  // Create space for new palette
			palette = new unsigned char[768];
		 
			if(palette == NULL)
				return NO_ENOUGH_MEMORY;
		 
		  // VGA palette is the 768 bytes following the header
			memcpy(palette, &imagedata[imagedata[0]+18], 768);
		 
		  // Palette entries are BGR ordered so we have to convert to RGB
			for(iIndex = 0,iPalPtr = 0; iIndex != 256; ++iIndex, iPalPtr += 3){
				bTemp = palette[iPalPtr];               // Get Blue value
				palette[iPalPtr] = palette[iPalPtr+2]; // Copy Red to Blue
				palette[iPalPtr+2] = bTemp;             // Replace Blue at the end
			}

		case 2: // Raw RGB
   		
			if((imagesize + 18 + imagedata[0]) > filesize){
				return INVALID_FILE_SIZE;
			}
			
			if(imagedata[1] != 0){
				return INVALID_FILE_HEADER;
			}

			ret = loadRawTga();
			if (ret > 0)
				return ret;

			BgrtoRgb(); 
       		break;
      
      case 3:

			ret = loadRawTga();
			if (ret > 0)
				return ret;
			break;     
      		

		default:
			return INVALID_FILE;
    }

//   if((imagedata[17] & 0x20)==0) 
//     FlipImg();

	return true;

}

int Image::loadRawTga(){

	short offset;
    unsigned char *auxdata;
 
	if(imagedata)
		delete [] imagedata;

	auxdata = new unsigned char[imagesize];

	if(auxdata == NULL)
		return NO_ENOUGH_MEMORY;

	offset = imagedata[0] + 18; // Add header to ident field size

	if(imagedata[1] == 1) // Indexed images
		offset += 768;  // Add palette offset

	memcpy(auxdata, &imagedata[offset], imagesize);
//	delete imagedata;
	imagedata = auxdata;
	return 0;
}

void Image::BgrtoRgb(){
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

int Image::writeTga(char* filename, short int width, short int height, unsigned char depth,
		unsigned char* data){
	
	unsigned char cGarbage = 0, type, mode;
	short int iGarbage = 0;
	int i;
	FILE *file;

	file = fopen(filename, "wb");
	if (file == NULL) {
		return FILE_NOT_FOUND;
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
	return 0;

}
