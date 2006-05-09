#ifndef _HEIGHTMAP_H_
#define _HEIGHTMAP_H_

#include "../math/algebra.h"
#include <string>

class heightmap{
	
public:

	heightmap(){};
	heightmap(std::string filename, int sizex, int sizey);
	~heightmap();
	
	bool initialize(std::string filename, int sizex, int sizey);
	
	
private:
	
	vec3 *terrainVerts;
	
};

#endif //_HEIGHTMAP_H_
