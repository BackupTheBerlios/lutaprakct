
#include "heightmap.h"
#include "../../../../util/image/tgaimage.h"
#include <iostream>

Heightmap::~Heightmap(){
	if (data)
		delete data;
}


