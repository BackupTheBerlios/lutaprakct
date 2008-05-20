#ifndef GLSLSHADER_H_
#define GLSLSHADER_H_

#include <GL/gl.h>
#include "glextensions.h"

class GlslShader{
	
	public: 
		GlslShader();
		GlslShader(const char* vertexSource, const char* fragmentSource);
		virtual ~GlslShader();
	
		bool initialize(const char* vertexSource,const char* fragmentSource);
		void kill();
		void bind();
		void unbind();
	
		GLcharARB* getCompilerLog();
	
	protected:
	
		GLhandleARB fragment, vertex, program;
	
};

#endif /*GLSLSHADER_H_*/
