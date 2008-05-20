#include <iostream>
#include "Fbo.h"
#include "glextensions.h"

void Fbo::initialize(){

    glGenFramebuffersEXT(1, &framebufferID);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebufferID);		
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

//TODO alterando o estados das texturas
bool Fbo::addDepthTexture(){

/*    glGenTextures(1, &shadowTextureID);
    glBindTexture(GL_TEXTURE_2D, shadowTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FAIL_VALUE_ARB, 0.5f);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);*/
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebufferID);
	glGenTextures(1, &shadowTextureID);
	glBindTexture(GL_TEXTURE_2D, shadowTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 512, 512, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
//	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, shadowTextureID, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, shadowTextureID, 0);
	checkFramebufferStatus(false);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	return true;
}

bool Fbo::addRenderBuffer(int sizex, int sizey){
	
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebufferID);
    
    glGenRenderbuffersEXT(1, &renderbufferID);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderbufferID);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, sizex, sizey);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, renderbufferID);
    
//    glDrawBuffer(GL_NONE);
//    glReadBuffer(GL_NONE);
    
    if (!checkFramebufferStatus(false)){
    	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    	return false;
    }
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	return true;
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

void Fbo::bind(){
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebufferID);	
}

void Fbo::unbind(){
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}
