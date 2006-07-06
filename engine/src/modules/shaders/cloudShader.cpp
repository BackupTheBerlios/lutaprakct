
#include "cloudShader.h"

void cloudShader::setInitialParameters(){

	animation[0] = 0.0;
	animation[1] = 0.0;
	animation[2] = 0.0;

	GLint loc = glGetUniformLocationARB(program, "Noise");
	if (loc == -1)
	    	return;	
	glUniform1iARB( loc, 0);	
	return;
	
}

void cloudShader::setLoopParameters(){

	GLint loc = glGetUniformLocationARB(program, "Offset");
	if (loc == -1)
	    	return;
	
	animation[2] += 0.0003;
	animation[1] += 0.0003;
	
	glUniform3fARB( loc, animation[0], animation[1], animation[2]);	
	return;
	
}
