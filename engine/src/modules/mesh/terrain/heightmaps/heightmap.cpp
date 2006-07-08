
#include "heightmap.h"
#include "../../../../util/image/tgaimage.h"
#include <iostream>

Heightmap::~Heightmap(){
	if (data){
		free(data);
		data = NULL;
	}
}

void Heightmap::saveTga(std::string filename, short int sizex, short int sizey, short int depth, unsigned char* data){
	tgaimage *tga = new tgaimage();
	tga->write(filename.c_str(), sizex, sizey, depth, data);
	delete tga;	

}

void Heightmap::clearData(){
	if (data){
		free(data);
		data = NULL;
	}
}	