#ifndef _BASICLIGHTMATERIAL_H_
#define _BASICLIGHTMATERIAL_H_

#include "material.h"
#include "../shaders/cgshaders/pixelLightShader.h"

/*
 * esse material eh o tipo basico de per pixel light
 * usa um shader simples, outros materials podem ser feitos usando efeitos
 * mais elaborados como normal map, etc
 */

class basicLightMaterial : public material{
	
public:

	basicLightMaterial() : shader(NULL){ };
	basicLightMaterial(std::string filename) : shader(NULL){ initialize(filename); };
	virtual ~basicLightMaterial();
	
	void initialize(std::string filename);
	virtual void bind();
	virtual void unbind();
	
public:
	
	pixelLightShader *shader;
};

#endif //_BASICLIGHTMATERIAL_H_
