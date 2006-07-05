
#include "cloudShader.h"
#include <iostream>

void cloudShader::setInitialParameters(){

	GLint loc = glGetUniformLocationARB(program, "Noise");
	if (loc == -1){
		std::cout<< "variavel nao encontrada" << std::endl;
    	return;
	}	
	glUniform1iARB( loc, 0);	
	return;
	
}
