#ifndef BASICTEXTUREMATERIAL_H_
#define BASICTEXTUREMATERIAL_H_

#include "material.h"

class BasicTextureMaterial : public material{
	
	public:
	
	BasicTextureMaterial(){};
	virtual ~BasicTextureMaterial(){};
	
	virtual void initialize(std::string filename);
	virtual void bind();
	virtual void unbind();
	
};

#endif /*BASICTEXTUREMATERIAL_H_*/
