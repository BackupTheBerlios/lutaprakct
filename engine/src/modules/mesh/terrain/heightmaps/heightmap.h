#ifndef _HEIGHTMAP_H_
#define _HEIGHTMAP_H_

#include <string>
#include <iostream>

//essa classe GERA as imagens tga dos heightmaps

class Heightmap{
	
public:
	//contrutor e destrutor
	Heightmap(){ data = NULL; };
	virtual ~Heightmap();
	
	bool load(std::string& filename);
	void save(std::string& filename);
	void clearData();
	
	//sets e gets
	int getSizeX(){return sizex; }
	int getSizeY(){return sizey; }
	void setSizeX(int x){ sizex = x; }
	void setSizeY(int y){ sizey = y; }
	
	unsigned char* data;
	
protected:
	
	short int sizex, sizey;
	
};

#endif //_HEIGHTMAP_H_
