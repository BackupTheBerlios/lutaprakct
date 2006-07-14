#ifndef _PIXELLIGHTSHADER_H_
#define _PIXELLIGHTSHADER_H_

#include "../../../util/cghelper/cgShader.h"
#include <cstdio>


class pixelLightShader : public cgShader {
	
public:

	pixelLightShader(){};
	pixelLightShader(char *vertexfile, int vertex, char * fragmentfile, int fragment, int flags ) { initialize(vertexfile,  vertex,  fragmentfile,  fragment, flags); };
	virtual ~pixelLightShader(){kill();};

	virtual void setInitialParameters(materialData *config);
	virtual void setLoopParameters(materialData *config);
	
private:
	
	//CGparameter Light;
	CGparameter ModelViewProj;
	//CGparameter ModelViewIT;
	CGparameter globalAmbient;
	CGparameter lightColor;
	CGparameter lightPosition;
	CGparameter eyePosition;
	CGparameter ke;
	CGparameter ka;
	CGparameter kd;
	CGparameter ks;
	CGparameter shininess;
	
	CGparameter lights;
	
};


#endif //_PIXELLIGHTSHADER_H_
