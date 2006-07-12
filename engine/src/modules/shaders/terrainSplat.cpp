
#include "terrainSplat.h"

#include <iostream>

void terrainSplat::setInitialParameters(){
	
	
	
	texture0 = glGetUniformLocationARB(program, "tex0");
	if (texture0 == -1){
		std::cout << "texture0 nao encontrada" << std::endl;
	    	return;	
	}
	glUniform1iARB( texture0, 0);
	
	texture1 = glGetUniformLocationARB(program, "tex1");
	if (texture1 == -1){
		std::cout << "texture1 nao encontrada" << std::endl;
	    	return;	
	}
	glUniform1iARB( texture1, 1 );
	
/*	alphamap = glGetUniformLocationARB(program, "alphamap");
	if (alphamap == -1){
		std::cout << "alphamap nao encontrada" << std::endl;
	    	return;	
	}
	glUniform1iARB( alphamap, 2);*/
	
}
