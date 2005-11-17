#ifndef _BASICLIGHTMATERIAL_H_
#define _BASICLIGHTMATERIAL_H_

#include "material.h"

/*
 * esse material eh o tipo basico de per pixel light
 * usa um shader simples, outros materials podem ser feitos usando efeitos
 * mais elaborados como normal map, etc
 */

class basicLightMaterial : public material{
	
public:

	basicLightMaterial();
	virtual ~basicLightMaterial();
	
	void initialize(std::string filename);
	virtual void bind();
	virtual void unbind();
	
private:
	
	
	
};

#endif //_BASICLIGHTMATERIAL_H_
