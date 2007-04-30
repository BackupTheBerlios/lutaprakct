
#include "heightmap.h"
#include "../../../../util/image/tgaimage.h"
#include <iostream>

Heightmap::~Heightmap(){
	if (data){
		delete []data;
		data = NULL;
	}
}

bool Heightmap::load(std::string& filename){
	
	TgaImage* tga = new TgaImage(filename);
	sizex = tga->getWidth();
	sizey = tga->getHeight();
	
	data = new unsigned char[sizex * sizey];
	
	int j = 0;
	for (int i = 0; i < sizex*sizey; i++){
		(data[i]) = (tga->imagedata[j]);
		j += 3;
	}
	
	delete tga;
	return true;
}

void Heightmap::save(std::string& filename){
	TgaImage* tga = new TgaImage();
	unsigned char* greyToRGBData = new unsigned char[sizex * sizey * 3];
	
	int j = 0;
	for (int i = 0; i < sizex*sizey; i++){
		greyToRGBData[j++] = data[i];
		greyToRGBData[j++] = data[i];
		greyToRGBData[j++] = data[i];
	}
	tga->write(filename, sizex, sizey, 24, greyToRGBData);
	delete []greyToRGBData;
	delete tga;
}

void Heightmap::clearData(){
	if (data){
		delete data;
		data = NULL;
	}
}

