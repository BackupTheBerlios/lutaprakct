
#include "glslShader.h"

glslShader::glslShader(){
}

glslShader::~glslShader(){
}

bool glslShader::initialize(char* vertexSource, char* fragmentSource){

	if (vertexSource){
		vertex = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
		
	}
	
	if (fragmentSource){
		fragment = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	}
	
}