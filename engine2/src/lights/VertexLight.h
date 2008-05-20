#ifndef VERTEXLIGHT_H_
#define VERTEXLIGHT_H_

#include "Light.h"

class VertexLight : public Light{
	
	public:
	
		VertexLight();
		~VertexLight();
	
		virtual bool initialize(unsigned int id) = 0;
		virtual void shutdown() = 0;
		
		virtual void bind() = 0;
		virtual void unbind() = 0;
	
	
};

#endif /*VERTEXLIGHT_H_*/
