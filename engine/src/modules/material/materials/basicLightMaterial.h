#ifndef _BASICLIGHTMATERIAL_H_
#define _BASICLIGHTMATERIAL_H_

#include "../material.h"
#include "../../shaders/cgshaders/pixelLightShader.h"

/*
 * esse material eh o tipo basico de per pixel light
 * usa um shader simples, outros materials podem ser feitos usando efeitos
 * mais elaborados como normal map, etc
 */

class BasicLightMaterial : public Material{
	
public:

	BasicLightMaterial() : shader(NULL){ };
	BasicLightMaterial(std::string& filename) : shader(NULL){ initialize(filename); };
	virtual ~BasicLightMaterial();
	
	void initialize(std::string& filename);
	virtual void bind();
	virtual void unbind();
	
public:
	
	PixelLightShader *shader;
};

#endif //_BASICLIGHTMATERIAL_H_
