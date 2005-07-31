
#include "map.h"
#include <cstdlib>

world::world(): mapCells(0), width(0), height(0){
}

world::~world(){
}

bool world::initialize(int width, int height){
	if (width <=0)
		return false;
	if (height<= 0)
		return false;
	if (!mapCells)
		delete []mapCells;
		
	mapCells = new mapCell[width*height];
	this->width = width;
	this->height = height;
	
	return true;
}
	
void world::shutdown(){
	
	if (!mapCells)
		delete []mapCells;
	height = 0;
	width = 0;
}

mapCell* world::getMapCell(int x, int y){

	if (isInsideMap(x, y))
		return mapCells + y * width + x;
	
}	
