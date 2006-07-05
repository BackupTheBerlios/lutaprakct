#ifndef CLOUDSHADER_H_
#define CLOUDSHADER_H_

#include "glslShader.h"

class cloudShader : public glslShader{
	
	public:
	
		cloudShader(){};
		cloudShader(const char* vertexSource, const char* fragmentSource){ initialize(vertexSource, fragmentSource);};
		~cloudShader(){kill();};
		
		void setInitialParameters();
	
};

#endif /*CLOUDSHADER_H_*/
