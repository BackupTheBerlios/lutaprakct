#ifndef CLOUDSHADER_H_
#define CLOUDSHADER_H_

#include "../../../util/glhelper/glslShader.h"

class cloudShader : public glslShader{
	
	public:
	
		cloudShader(){};
		cloudShader(const char* vertexSource, const char* fragmentSource){ initialize(vertexSource, fragmentSource);};
		~cloudShader(){kill();};
		
		void setInitialParameters();
		void setLoopParameters();
		
	private:
		
		GLint time;
		float animation[3];
	
};

#endif /*CLOUDSHADER_H_*/