#ifndef SHLIGHT_H_
#define SHLIGHT_H_

#include "Light.h"
#include "../util/glhelper/glslShader.h"

//Spherical Harmonics Lightning

class ShLight : public Light {
	
	public:
	
		ShLight();
		~ShLight();
	
		virtual bool initialize(unsigned int id);
		virtual void shutdown();
		
		virtual void bind();
		virtual void unbind();
		
	private:
	
		GlslShader shader;
		
};

#endif /*SHLIGHT_H_*/
