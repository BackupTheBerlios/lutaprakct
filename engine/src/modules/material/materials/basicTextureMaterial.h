#ifndef BASICTEXTUREMATERIAL_H_
#define BASICTEXTUREMATERIAL_H_

#include "../material.h"

/*esse material é so uma textura. usado em testes*/

class BasicTextureMaterial : public Material{
	
	public:
	
	BasicTextureMaterial(){};
	BasicTextureMaterial(std::string& filename){ initialize(filename); };
	virtual ~BasicTextureMaterial(){};
	
	virtual void initialize(std::string& filename);
	virtual void bind();
	virtual void unbind();
	
};

#endif /*BASICTEXTUREMATERIAL_H_*/
