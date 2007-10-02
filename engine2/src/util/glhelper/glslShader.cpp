
#include "glslShader.h"

GlslShader::GlslShader(){
}

GlslShader::GlslShader(const char* vertexSource, const char* fragmentSource){
	initialize(vertexSource, fragmentSource);
}

GlslShader::~GlslShader(){
	kill();
}

//TODO checar erros de compilacao e de linkagem
bool GlslShader::initialize(const char* vertexSource, const char* fragmentSource){

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

void GlslShader::kill(){
	
	glDeleteObjectARB(vertex);
	glDeleteObjectARB(fragment);
	glDeleteObjectARB(program);
	
}

void GlslShader::bind(){
	glUseProgramObjectARB(program);	
}

void GlslShader::unbind(){
	glUseProgramObjectARB(0);
}

GLcharARB* GlslShader::getCompilerLog(){
	
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

