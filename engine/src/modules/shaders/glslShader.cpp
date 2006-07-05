
#include "glslShader.h"

glslShader::glslShader(){
}

glslShader::glslShader(const char* vertexSource, const char* fragmentSource){
	initialize(vertexSource, fragmentSource);
}

glslShader::~glslShader(){
	kill();
}

//TODO checar erros de compilacao e de linkagem
bool glslShader::initialize(const char* vertexSource, const char* fragmentSource){

	if (vertexSource || fragmentSource)
		program = glCreateProgramObjectARB();
	else
		return false;

	if (vertexSource){
		vertex = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
		glShaderSourceARB(vertex, 1, &vertexSource, NULL);
		glCompileShaderARB(vertex);
		glAttachObjectARB(program, vertex);		
	}
	
	if (fragmentSource){
		fragment = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
		glShaderSourceARB(fragment, 1, &fragmentSource, NULL);
		glCompileShaderARB(fragment);
		glAttachObjectARB(program, fragment);
	}
	
	glLinkProgramARB(program);
	
	return true;
	
}

void glslShader::kill(){
	
	glDeleteObjectARB(vertex);
	glDeleteObjectARB(fragment);
	glDeleteObjectARB(program);
	
}

void glslShader::bind(){
	glUseProgramObjectARB(program);	
}

void glslShader::unbind(){
	glUseProgramObjectARB(0);
}

GLcharARB* glslShader::getCompilerLog(){
	
	int infologlen = 0;
	int charswritten = 0;
	GLcharARB *infolog;
	
	glGetObjectParameterivARB( program, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infologlen );
	
	if (infologlen > 0){
		infolog = new GLcharARB[infologlen];
		if (infolog == NULL)
			return NULL;
		glGetInfoLogARB(program, infologlen, &charswritten, infolog);
		return infolog;
	}
	
	return NULL;
}

