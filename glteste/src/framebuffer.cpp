
#include "framebuffer.h"

framebuffer::~framebuffer(){

	glDeleteTextures(1, (GLuint*) &(texturas[0]->texID));
	glDeleteFramebuffersEXT(1, (GLuint*) &(framebufferID));
	
}

void framebuffer::addTexture(int target, int format, int internalFormat, int flags, int sizex, int sizey){

	GPU_glsprite *auxsprite = new GPU_glsprite;
	auxsprite->sizex = sizex;
	auxsprite->sizey = sizey;
	auxsprite->textureflags = flags;
	
	if (target == TEXTURE_2D)
		auxsprite->textarget = GL_TEXTURE_2D;
	else if (target == TEXTURE_RECT_ARB)
		auxsprite->textarget = GL_TEXTURE_RECTANGLE_ARB;
	else if (target == TEXTURE_RECT_NV)
		auxsprite->textarget = GL_TEXTURE_RECTANGLE_NV;
	else
		return;
		
	if (internalFormat == INTERNAL_BGR)
		auxsprite->internalformat = GL_BGR;
	else if (internalFormat == INTERNAL_BGRA)
		auxsprite->internalformat = GL_BGR;
	else if (internalFormat == INTERNAL_RGB)
		auxsprite->internalformat = GL_RGB;
	else if (internalFormat == INTERNAL_RGBA)
		auxsprite->internalformat = GL_RGBA;
	else 
		return;
		
		
	if (format == INTERNAL_BGR)
		auxsprite->format = GL_BGR;
	else if (format == INTERNAL_BGRA)
		auxsprite->format = GL_BGR;
	else if (format == INTERNAL_RGB)
		auxsprite->format = GL_RGB;
	else if (format == INTERNAL_RGBA)
		auxsprite->format = GL_RGBA;
	else 
		return;
		
	texturas.push_back(auxsprite);

}

void framebuffer::initialize(){
	
     glGenFramebuffersEXT(1,  &framebufferID); 
     glGenTextures(1,  &(texturas[0]->texID));
     
     glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebufferID);
     glBindTexture( texturas[0]->textarget, (texturas[0]->texID) );
     glTexImage2D( texturas[0]->textarget, 0, texturas[0]->internalformat, 
		               texturas[0]->sizex, texturas[0]->sizey, 0, texturas[0]->format, 
									 GL_UNSIGNED_BYTE, NULL);
     glTexParameterf( texturas[0]->textarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
     glTexParameterf( texturas[0]->textarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
     glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT ,
		 														 texturas[0]->textarget, texturas[0]->texID, 0);

     glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
     glBindTexture(texturas[0]->texID, 0);
	
}

void framebuffer::bind(){
	
    glBindTexture(texturas[0]->textarget, 0);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebufferID);
    
}

void framebuffer::unbind(){
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glDisable(texturas[0]->textarget);
}
