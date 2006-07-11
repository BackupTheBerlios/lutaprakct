
#include "terrainSplat.h"

#include <iostream>

void terrainSplat::setInitialParameters(){
	
	texture0 = glGetUniformLocationARB(program, "arido");
	if (texture0 == -1){
		std::cout << "uniform 2 nao encontrada" << std::endl;
	    	return;	
	}
	glUniform1iARB( texture0, 0);
	
	texture1 = glGetUniformLocationARB(program, "grama");
	if (texture1 == -1){
		std::cout << "uniform 2 nao encontrada" << std::endl;
	    	return;	
	}
	glUniform1iARB( texture1, 1 );
	
	alphamap = glGetUniformLocationARB(program, "alphamap");
	if (alphamap == -1){
		//std::cout << "uniform 1 nao encontrada" << std::endl;
	    	return;	
	}
	glUniform1iARB( alphamap, 2);
	
}
