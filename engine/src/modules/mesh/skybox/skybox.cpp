
#include "skybox.h"
#include "../../../../libs/tinyxml/tinyxml.h"
#include "../../../util/glhelper/shapes.h"
#include <iostream>

bool Skybox::initialize(std::string& filename, float size, int followcamera, int enabled ){

	int flags = Texture::CLAMP_TO_EDGE;
	flags |= Texture::LINEAR_MIPMAP_LINEAR;
	flags |= Texture::MIPMAP_SGI;
	flags |= Texture::COMPRESSION_ARB;

	this->size = size;
	this->followcamera = followcamera;
	this->enabled = enabled;
	
	cube = new Texture( filename, Texture::TEXTURE_CUBEMAP, Texture::RGB, Texture::RGB8, flags );
	return true;
}


void Skybox::draw(){

	glDisable(GL_DEPTH_TEST);
	
	cube->bind();
	float s_splane[] = { 1.0, 0.0, 0.0, 0.0 };
	float t_splane[] = { 0.0, 1.0, 0.0, 0.0 };
	float r_splane[] = { 0.0, 0.0, 1.0, 0.0 };
	glTexGenfv(GL_S, GL_OBJECT_PLANE, s_splane);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, t_splane);
	glTexGenfv(GL_R, GL_OBJECT_PLANE, r_splane);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		
		if (followcamera){
			float mat[16];
			glGetFloatv(GL_MODELVIEW_MATRIX, mat);
			mat[12] = mat[13] = mat[14] = 0.0;
			glLoadMatrixf(mat);
		}
		
		solidCube( size );
	
	glPopMatrix();
	
	cube->unbind();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);	
	glEnable(GL_DEPTH_TEST);
	
}

