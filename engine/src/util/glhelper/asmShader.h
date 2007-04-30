#ifndef ARBSHADER_H_
#define ARBSHADER_H_

#include <GL/gl.h>
#include "../math/algebra.h"

class AsmShader {
public:
	AsmShader(const char *src);
	~AsmShader();
	
	void enable();
	void disable();
	void bind();
	
	void envParameter(GLuint index,const vec4 &p);
	void localParameter(GLuint index,const vec4 &p);
	void namedParameter(const char *name,const vec4 &p);
	
	GLuint target;
	GLuint id;
};


#endif /*ARBSHADER_H_*/
