#ifndef MATERIALFACTORY_H_
#define MATERIALFACTORY_H_

#include "material.h"

class MaterialFactory{
	
	public:
	
	static Material* loadMaterial(std::string& filename); 
	
};

#endif /*MATERIALFACTORY_H_*/
