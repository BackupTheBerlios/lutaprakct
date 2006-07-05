#ifndef GLSLSHADER_H_
#define GLSLSHADER_H_

#include <GL/gl.h>
#include "../../util/glext/glextensions.h"

class glslShader{
	
	public: 
		glslShader();
		glslShader(const char* vertexSource, const char* fragmentSource);
		virtual ~glslShader();
	
		bool initialize(const char* vertexSource,const char* fragmentSource);
		void kill();
		void bind();
		void unbind();
	
		GLcharARB* getCompilerLog();
	
	protected:
	
		GLhandleARB fragment, vertex, program;
	
};

#endif /*GLSLSHADER_H_*/
