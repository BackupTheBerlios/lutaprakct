
#include "basicTextureMaterial.h"

void BasicTextureMaterial::initialize(std::string filename){

	addBaseTexture(filename, 0);
	
}

void BasicTextureMaterial::bind(){
	
	std::list<texture *>::iterator iter;
	iter = baseTextures.begin();
	
	if (iter != baseTextures.end())
		(*iter)->bind();
	
}

void BasicTextureMaterial::unbind(){
	
	std::list<texture *>::iterator iter;
	iter = baseTextures.begin();
	
	(*iter)->unbind();	
	
}
