
#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include <GL/gl.h>
#include "util/glext/glextensions.h"
#include <vector>
#include "SDL_gpu.h"

class framebuffer{
	
	public:
		
		framebuffer(){};
		virtual ~framebuffer();
		
		void initialize();
		void addTexture(int target, int format, int internalFormat, int flags, int sizex, int sizey);	//	void addRenderBuffer();
		void bind();
		void unbind();
	
	private:
		GLuint framebufferID;
		
		std::vector<GPU_glsprite*> texturas;
};


#endif
