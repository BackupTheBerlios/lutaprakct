
#include "heightmap.h"
#include "../../../util/image/tgaimage.h"
#include <iostream>

heightmap::heightmap(std::string filename, int sizex, int sizey){
	terrainVerts = NULL;
	initialize(filename, sizex, sizey);
}

heightmap::~heightmap(){
	if (terrainVerts)
		delete terrainVerts;
}

bool heightmap::initialize(std::string filename, int sizex, int sizey){

	if (terrainVerts)
		delete terrainVerts;
	
	tgaimage *heightmap = new tgaimage(filename.c_str());
	
	terrainVerts 	 = new float [sizex * sizey];
	
	for(int i=0; i<sizex; i++){
		for(int j=0; j<sizey; j++){
			int indice = (i*sizex + j);
			float height =  (float) (heightmap)->imagedata[indice]/ 255.0;
			terrainVerts[indice] = height;
		}
	}
	
	delete heightmap;
	this->sizex = sizex;
	this->sizey = sizey;
	
	return true;
}

void heightmap::scale(float min,float max) {

	float amp,aux,min1,max1,height;
	int total,i;

	if (terrainVerts == NULL)
		return;

	if (min > max) {
		aux = min;
		min = max;
		max = aux;
	}

	amp = max - min;
	total = sizex * sizey;

	min1 = terrainVerts[0];
	max1 = terrainVerts[0];
	for(i=1;i < total ; i++) {
		if (terrainVerts[i] > max1)
			max1 = terrainVerts[i];
		if (terrainVerts[i] < min1)
			min1 = terrainVerts[i];
	}
	for(i=0;i < total; i++) {
		height = (terrainVerts[i] - min1) / (max1-min1);
		terrainVerts[i] = height * amp - min;
	}

}

int heightmap::generateDisplayList(float xOffset, float yOffset, float zOffset) {

	GLuint terrainDL;
	float startW,startL;
	int i,j;

	startW = sizey / 2.0 - sizey;
	startL = - sizex / 2.0 + sizex;

	terrainDL = glGenLists(1);

	glNewList(terrainDL,GL_COMPILE);

	for (i = 0 ; i < sizex-1; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0;j < sizey; j++) {
		
			glVertex3f(
				startW + j + xOffset,
				terrainVerts[(i+1)*sizex + (j)] + yOffset,
				startL - (i+1) + zOffset);

			glVertex3f(
				startW + j + xOffset, 
				terrainVerts[(i)*sizex + j] + yOffset,
				startL - i + zOffset);					
		}
		glEnd();
	}
	glEndList();
	return(terrainDL);
}
