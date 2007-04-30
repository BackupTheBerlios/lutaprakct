
#include "fbo.h"
#include <iostream>

bool Fbo::initialize(int x, int y){

	usecolorbuffer = usedepthbuffer = userenderbuffer = false;
	sizex = x;
	sizey = y;
	
	glGenFramebuffersEXT(1, &framebuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	
	
	return true;
}

bool Fbo::addDepthBuffer(){
	
	usedepthbuffer = true;
	glGenTextures(1, &depthbuffer);
	glBindTexture(GL_TEXTURE_2D, depthbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, sizex, sizey, 0, GL_DEPTH_COMPONENT, 
				GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depthbuffer, 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	
	return checkFramebufferStatus();
}

bool Fbo::checkFramebufferStatus(bool silent){

	GLenum status;
	status = (GLenum) glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	
	switch(status){
		case GL_FRAMEBUFFER_COMPLETE_EXT:
			return true;
		case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
			if (!silent) std::cout << "Framebuffer nao suportado." << std::endl;
			return false;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
			if (!silent) std::cout << "Framebuffer incompleto, faltando anexo." << std::endl;
			return false;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
			if(!silent) std::cout << "Framebuffer incompleto, anexo duplicado." << std::endl;
			return false;
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
			if(!silent) std::cout << "Framebuffer incompleto, imagens devem ter mesma dimensao." << std::endl;
			return false;
		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
			if (!silent) std::cout << "Framebuffer incompleto, imagens devem ter mesmo formato." << std::endl;
			return false;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
			if (!silent) std::cout << "Framebuffer incompleto, faltando draw buffer." << std::endl;
			return false;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
			if (!silent) std::cout << "Framebuffer incompleto, faltando read buffer." << std::endl;
			return false;
		default:
			return false;
	}
	return true;
	
}

bool Fbo::addColorBuffer(){
	usecolorbuffer = true;
	
	glGenTextures(1, &colorbuffer);
	glBindTexture(GL_TEXTURE_2D, colorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizex, sizey, 0, GL_RGB, 
				GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, colorbuffer, 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	return checkFramebufferStatus();
}

bool Fbo::addRenderBuffer(){
	userenderbuffer = true;
	glGenRenderbuffersEXT(1, &renderbuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizex, sizey, 0, GL_RGB, 
				GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, sizex, sizey);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, renderbuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	
	return checkFramebufferStatus();
}  

void Fbo::bind(){
	glViewport(0, 0, sizex, sizey);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
}

void Fbo::unbind(){
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glViewport(0, 0, 800, 600);
}

void Fbo::shutdown(){
	
//	if (userenderbuffer)
//		glDeleteRenderbuffersEXT(renderbuffer);
	
//	glDeleteFramebuffersEXT(framebuffer);
}
