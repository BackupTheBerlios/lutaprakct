
#include "texture.h"
#include "../../../util/glext/glextensions.h"
#include <cstdlib>
#include <iostream>

#include <SDL/SDL.h>

texture::~texture(){
	if (img)
		delete img;
}

texture::texture(char* filename, int target, int format, int internalformat, int flags) : img(NULL), flags(flags){
	img = NULL;
	load(filename, target, format, internalformat, flags);
}

void texture::enable(){
	glEnable(target);
}

void texture::disable(){
	glDisable(target);
}

void texture::unbind(){
	glDisable(target);
}

void texture::bind(){
	glEnable(target);
	GLfloat parm;
	glGetTexParameterfv(target, GL_TEXTURE_WRAP_S, &parm);
	if (flags & CLAMP){
		if (parm != GL_CLAMP){
			glTexParameteri(target,GL_TEXTURE_WRAP_S,GL_CLAMP);
			glTexParameteri(target,GL_TEXTURE_WRAP_T,GL_CLAMP);
			glTexParameteri(target,GL_TEXTURE_WRAP_R,GL_CLAMP);
		}
	} 
	else if (flags & CLAMP_TO_EDGE) {
		if (parm != GL_CLAMP_TO_EDGE){
			glTexParameteri(target,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
			glTexParameteri(target,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
			glTexParameteri(target,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
		}
	}
	else {
			glTexParameteri(target,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameteri(target,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexParameteri(target,GL_TEXTURE_WRAP_R,GL_REPEAT);
	}

	glBindTexture(target, id);
}

void texture::unload(){
	glDeleteTextures(1, &id);
}

bool texture::load(char* filename, int target, int format, int internalformat, int flags){
	this->flags = flags;
	this->target = target;
	
	//primeiro verifica o formato. se tiver compressao o formato interno deve ser outro
	//se nao tiver compressao recebe o formato interno passado
	if ( format == RGB ){
		this->format = GL_RGB;
		if (flags &COMPRESSION_ARB)
			this->internalformat = GL_COMPRESSED_RGB_ARB;
		else if (flags &COMPRESSION_DXT1) //RGB so aceita DXT1
			this->internalformat = COMPRESSED_RGB_S3TC_DXT1_EXT;
		else
			this->internalformat = internalformat;
	}
	else if (format == RGBA) {
		this->format = GL_RGBA;
		if (flags &COMPRESSION_ARB)
			this->internalformat = GL_COMPRESSED_RGBA_ARB;
		else if (flags &COMPRESSION_DXT1)
			this->internalformat = COMPRESSED_RGBA_S3TC_DXT1_EXT;
		else if (flags &COMPRESSION_DXT3)
			this->internalformat = COMPRESSED_RGBA_S3TC_DXT3_EXT;
		else if (flags &COMPRESSION_DXT5)
			this->internalformat = COMPRESSED_RGBA_S3TC_DXT5_EXT;
		else
			this->internalformat = internalformat;
	}
	
	else if (format == BGR){
		this->format = GL_BGR_EXT;
		if (flags &COMPRESSION_ARB)
			this->internalformat = GL_COMPRESSED_RGB_ARB;
		else if (flags &COMPRESSION_DXT1) //RGB so aceita DXT1
			this->internalformat = COMPRESSED_RGB_S3TC_DXT1_EXT;
		else
			this->internalformat = internalformat;
	}
	
	else if (format == BGRA){
		this->format = GL_BGRA_EXT;
		if (flags &COMPRESSION_ARB)
			this->internalformat = GL_COMPRESSED_RGBA_ARB;
		else if (flags &COMPRESSION_DXT1)
			this->internalformat = COMPRESSED_RGBA_S3TC_DXT1_EXT;
		else if (flags &COMPRESSION_DXT3)
			this->internalformat = COMPRESSED_RGBA_S3TC_DXT3_EXT;
		else if (flags &COMPRESSION_DXT5)
			this->internalformat = COMPRESSED_RGBA_S3TC_DXT5_EXT;
		else
			this->internalformat = internalformat;
	}else {
		
		this->format = format;
		this->internalformat = internalformat;
		
	}
	
	glEnable(this->target);
	glGenTextures(1, &id);
	glBindTexture(this->target, id);
	
	//verifica algusn flags
	if (flags & CLAMP){
		glTexParameteri(this->target, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_R, GL_CLAMP);
	} 
	else if (flags & CLAMP_TO_EDGE) {
		glTexParameteri(this->target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
		
	if (flags & NEAREST){
		glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	} 
	else if (flags & LINEAR) {
		glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	} 
	else if (flags & NEAREST_MIPMAP_NEAREST) {
		if ( flags &MIPMAP_SGI)
			glTexParameteri(this->target, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	} 
	else if (flags & NEAREST_MIPMAP_LINEAR) {
		if ( flags &MIPMAP_SGI)
			glTexParameteri(this->target, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	} 
	else if (flags & LINEAR_MIPMAP_NEAREST) {
		if ( flags &MIPMAP_SGI)
			glTexParameteri(this->target, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	} 
	else if (flags & LINEAR_MIPMAP_LINEAR ) {
		if ( flags &MIPMAP_SGI)
			glTexParameteri(this->target, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	
	if (flags & ANISOTROPIC_2 )
		glTexParameteri(this->target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2);
	else if (flags & ANISOTROPIC_4)
		glTexParameteri(this->target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
	else if (flags & ANISOTROPIC_8)
		glTexParameteri(this->target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8);
	else if (flags & ANISOTROPIC_16)
		glTexParameteri(this->target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
	
	if (target == TEXTURE_1D){
		img = loadImage(filename);
		width = img->getWidth();
		height = 0;
		glTexImage1D(this->target, 0, this->internalformat, img->getWidth(), 0, this->format, GL_UNSIGNED_BYTE, img->imagedata);
	}
	else if ( (target == TEXTURE_2D) || (target == TEXTURE_RECTANGLE) || (target == TEXTURE_RECTANGLENV) ){
		img = loadImage(filename);
		width = img->getWidth();
		height = img->getHeight();
		glTexImage2D(this->target, 0, this->internalformat, img->getWidth(), img->getHeight(), 0, this->format, GL_UNSIGNED_BYTE, img->imagedata);
	}
	
	//nao carregue cubemaps com png.
	else if (target == TEXTURE_CUBEMAP) {
		char buff[1024];
		GLuint facetargets[] = {
			GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		};
		char *facenames[] = {"posx", "negx", "posy", "negy", "posz", "negz" };
		for (int i = 0; i < 6; i++){
			sprintf(buff, filename, facenames[i]);
			img = loadImage(filename);
			width = img->getWidth();
			height = img->getHeight();
			glTexImage2D(facetargets[i],0, this->internalformat, img->getWidth(), img->getHeight(), 0, this->format, GL_UNSIGNED_BYTE, img->imagedata);
			if (img->imagedata){
				delete img;
				img = NULL;
			}
		}
	}
	glDisable(target);
	//depois libera a memoria deletando a img
	if(img){
		//delete img;
		//img = NULL;
	}
	return id;
}
