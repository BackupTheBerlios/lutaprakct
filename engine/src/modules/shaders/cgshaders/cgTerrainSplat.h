#ifndef CGTERRAINSPLAT_H_
#define CGTERRAINSPLAT_H_

#include "../../../util/cghelper/cgShader.h"

class CgTerrainSplat : public CgShader{
	
	public:
	
	CgTerrainSplat(){};
	CgTerrainSplat(char *vertexfile, int vertex, char * fragmentfile, int fragment, int flags ) { initialize(vertexfile,  vertex,  fragmentfile,  fragment, flags); };
	virtual ~CgTerrainSplat(){kill();};

	virtual void setInitialParameters(void* config){};
	virtual void setLoopParameters(void* config){};
	
	
};

#endif /*CGTERRAINSPLAT_H_*/
