
#include "heightmap.h"
#include "../../../../util/image/tgaimage.h"
#include <iostream>

Heightmap::~Heightmap(){
	if (data){
		delete []data;
		data = NULL;
	}
}

void Heightmap::saveTga(std::string filename, short int sizex, short int sizey, short int depth){
	tgaimage* tga = new tgaimage();
	unsigned char* greyToRGBData = new unsigned char[sizex * sizey * 3];
	
	int j = 0;
	for (int i = 0; i < sizex*sizey; i++){
		greyToRGBData[j++] = data[i];
		greyToRGBData[j++] = data[i];
		greyToRGBData[j++] = data[i];
	}
	tga->write(filename.c_str(), sizex, sizey, depth, greyToRGBData);
	delete []greyToRGBData;
	delete tga;
}

void Heightmap::clearData(){
	if (data){
		delete data;
		data = NULL;
	}
}

