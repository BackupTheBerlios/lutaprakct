#ifndef _HEIGHTMAP_H_
#define _HEIGHTMAP_H_

#include "../../../util/math/algebra.h"
#include <string>

class heightmap{
	
public:
	//contrutor e destrutor
	heightmap(){};
	heightmap(std::string filename, int sizex, int sizey);
	virtual ~heightmap();
	
	//inicializacao
	bool initialize(std::string filename, int sizex, int sizey);
	
	//manipulacao do terreno
	void scale(float min, float max);
	
	//renderizacao do terreno
	//TODO usar VBO e separar isso do terreno
	int generateDisplayList(float xOffset, float yOffset, float zOffset);
	
	//sets e gets
	int getSizeX(){return sizex; }
	int getSizeY(){return sizey; }
	void setSizeX(int x){ sizex = x; }
	void setSizeY(int y){ sizey = y; }
	
private:
	
	int sizex, sizey;
	float *terrainVerts;
	
};

#endif //_HEIGHTMAP_H_
