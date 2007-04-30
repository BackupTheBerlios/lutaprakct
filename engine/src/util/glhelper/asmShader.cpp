
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "asmShader.h"
#include "glextensions.h"

AsmShader::AsmShader(const char *src) {
	
	char *data;
	FILE *file = fopen(src,"r");
	if(file) {
		fseek(file,0,SEEK_END);
		int size = ftell(file);
		data = new char[size + 1];
		memset(data,0,size + 1);
		fseek(file,0,SEEK_SET);
		fread(data,1,size,file);
		fclose(file);
	} else {
		data = new char[strlen(src) + 1];
		strcpy(data,src);
	}
	
	int error = -1;
	if(!strncmp(data,"!!ARBvp1.0",10)) {
		target = GL_VERTEX_PROGRAM_ARB;
		glGenProgramsARB(1,&id);
		glBindProgramARB(target,id);
		glProgramStringARB(target,GL_PROGRAM_FORMAT_ASCII_ARB,strlen(data),data);
		glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB,&error);
	} else if(!strncmp(data,"!!ARBfp1.0",10)) {
		target = GL_FRAGMENT_PROGRAM_ARB;
		glGenProgramsARB(1,&id);
		glBindProgramARB(target,id);
		glProgramStringARB(target,GL_PROGRAM_FORMAT_ASCII_ARB,strlen(data),data);
		glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB,&error);
	} else if(!strncmp(data,"!!FP1.0",7)) {
		target = GL_FRAGMENT_PROGRAM_NV;
		glGenProgramsNV(1,&id);
		glBindProgramNV(target,id);
		glLoadProgramNV(target,id,strlen(data),(GLubyte*)data);
		glGetIntegerv(GL_PROGRAM_ERROR_POSITION_NV,&error);
	} else {
		target = 0;
		id = 0;
		char *s = data;
		while(*s && *s != '\n') s++;
		*s = '\0';
		fprintf(stderr,"unknown program header \"%s\" or error open \"%s\" file\n",data,src);
		delete data;
		return;
	}

	if(error != -1) {
		int line = 0;
		char *s = data;
		while(error-- && *s) if(*s++ == '\n') line++;
		while(s >= data && *s != '\n') s--;
		char *e = ++s;
		while(*e != '\n' && *e != '\0') e++;
		*e = '\0';
		fprintf(stderr,"program error at line %d:\n\"%s\"\n",line,s);
	}

	delete data;
}

AsmShader::~AsmShader() {
	if(target == GL_FRAGMENT_PROGRAM_NV) glDeleteProgramsNV(1,&id);
	else glDeleteProgramsARB(1,&id);
}
	
void AsmShader::enable() {
	glEnable(target);
}

void AsmShader::disable() {
	glDisable(target);
}

void AsmShader::bind() {
	if(target == GL_FRAGMENT_PROGRAM_NV) glBindProgramNV(target,id);
	else glBindProgramARB(target,id);
}

void AsmShader::envParameter(GLuint index,const vec4 &p) {
	float v[4];
	v[0] = p.x;
	v[1] = p.y;
	v[2] = p.z;
	v[3] = p.w;
	glProgramEnvParameter4fvARB(target, index, v);
}

void AsmShader::localParameter(GLuint index,const vec4 &p) {
	float v[4];
	v[0] = p.x;
	v[1] = p.y;
	v[2] = p.z;
	v[3] = p.w;
	glProgramLocalParameter4fvARB(target, index, v);
}

void AsmShader::namedParameter(const char *name,const vec4 &p) {
	float v[4];
	v[0] = p.x;
	v[1] = p.y;
	v[2] = p.z;
	v[3] = p.w;
	glProgramNamedParameter4fvNV(id,strlen(name),(GLubyte*)name,v);
}
