#ifndef CLOUDSHADER_H_
#define CLOUDSHADER_H_

#include "../../../util/glhelper/glslShader.h"

class CloudShader : public GlslShader{
	
	public:
	
		CloudShader(){};
		CloudShader(const char* vertexSource, const char* fragmentSource){ initialize(vertexSource, fragmentSource);};
		~CloudShader(){kill();};
		
		void setInitialParameters();
		void setLoopParameters();
		
	private:
		
		GLint time;
		float animation[3];
	
};

#endif /*CLOUDSHADER_H_*/
