#ifndef FBO_H_
#define FBO_H_

#include "glextensions.h"
#include <GL/gl.h> 

class Fbo{
	
	public:
	
		Fbo(){};
		~Fbo(){ shutdown(); };
		
		bool initialize(int sizex, int sizey);
		
		bool addDepthBuffer();
		bool addColorBuffer();
		bool addRenderBuffer();
		
		void bind();
		void unbind();
		
		bool checkFramebufferStatus( bool silent = true );
	
		void shutdown();
	
	private:
	
		GLuint framebuffer;
		
		GLuint colorbuffer;
		GLuint depthbuffer;
		GLuint renderbuffer;
		
		unsigned int sizex, sizey;
		bool usecolorbuffer, usedepthbuffer, userenderbuffer;
}; 

#endif /*FBO_H_*/
