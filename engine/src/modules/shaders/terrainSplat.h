#ifndef TERRAINSPLAT_H_
#define TERRAINSPLAT_H_

#include "glslShader.h"

class terrainSplat : public glslShader{
	
	public:
		
		terrainSplat(){};
		terrainSplat(const char* vertexSource, const char* fragmentSource){ initialize(vertexSource, fragmentSource);};
		virtual ~terrainSplat(){kill();};
			
		void setInitialParameters();
		void setLoopParameters(){};
		
	private:
	
		GLint alphamap;
		GLint texture0;
		GLint texture1;
	
};

#endif /*TERRAINSPLAT_H_*/
