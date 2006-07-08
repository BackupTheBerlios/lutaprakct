#ifndef _HEIGHTMAP_H_
#define _HEIGHTMAP_H_

#include <string>

//essa classe GERA as imagens tga dos heightmaps



class Heightmap{
	
public:
	//contrutor e destrutor
	Heightmap(){ data = NULL; };
	virtual ~Heightmap();
	
	//sets e gets
	int getSizeX(){return sizex; }
	int getSizeY(){return sizey; }
	void setSizeX(int x){ sizex = x; }
	void setSizeY(int y){ sizey = y; }
	
protected:
	
	unsigned short sizex, sizey;
	unsigned char* data;
	
};

#endif //_HEIGHTMAP_H_