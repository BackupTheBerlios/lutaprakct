#ifndef CGTERRAINSPLAT_H_
#define CGTERRAINSPLAT_H_

#include "../../../util/cghelper/cgShader.h"

class cgTerrainSplat : public cgShader{
	
	public:
	
	cgTerrainSplat(){};
	cgTerrainSplat(char *vertexfile, int vertex, char * fragmentfile, int fragment, int flags ) { initialize(vertexfile,  vertex,  fragmentfile,  fragment, flags); };
	virtual ~cgTerrainSplat(){kill();};

	virtual void setInitialParameters(materialData *config){};
	virtual void setLoopParameters(materialData *config){};
	
	
};

#endif /*CGTERRAINSPLAT_H_*/
