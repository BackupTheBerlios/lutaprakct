
#include "basicLightMaterial.h"
#include <iostream>

basicLightMaterial::~basicLightMaterial(){
	
	if (shader)
		shader->kill();
		
	if (materialConfig)
		delete materialConfig;
}

void basicLightMaterial::initialize(std::string file){
	
	if (!materialConfig)
		materialConfig = new materialData;
	/* le o file e seta os valores no materialConfig */
	
	materialConfig->shininess = 0.8;
	materialConfig->kSpecular[0] = 0.9;
	materialConfig->kSpecular[1] = 0.9;
	materialConfig->kSpecular[2] = 0.9;
	materialConfig->kEmissive[0] = 0.1;
	materialConfig->kEmissive[1] = 0.1;
	materialConfig->kEmissive[2] = 0.1;
	materialConfig->kAmbient[0] = 0.0;
	materialConfig->kAmbient[1] = 0.0;
	materialConfig->kAmbient[2] = 0.0;
	materialConfig->kDiffuse[0] = 0.5;	
	materialConfig->kDiffuse[1] = 0.5;	
	materialConfig->kDiffuse[2] = 0.5;	
	
	int flags = AUTOCOMPILE_MANUAL; 
	
	shader = new pixelLightShader("perpixellightv.cg" ,  PROFILE_ARBVP1, "perpixellightf.cg",  PROFILE_ARBFP1, flags);
	shader->setInitialParameters(materialConfig);
	
}

void basicLightMaterial::bind(){

	shader->setLoopParameters(materialConfig);
	shader->bind();	
	
}

void basicLightMaterial::unbind(){
	
	shader->unbind();
	
}
