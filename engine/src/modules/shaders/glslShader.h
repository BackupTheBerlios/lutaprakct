#ifndef GLSLSHADER_H_
#define GLSLSHADER_H_

#include <GL/gl.h>
#include "../../util/glext/glextensions.h"

class glslShader{
	
	public: 
		glslShader();
		~glslShader();
	
		bool initialize(char* vertexSource, char* fragmentSource);
		void kill();
		void bind();
		void unbind();
	
	private:
	
		GLhandleARB fragment, vertex, program;
	
};

#endif /*GLSLSHADER_H_*/
