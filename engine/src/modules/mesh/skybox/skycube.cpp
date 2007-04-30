
#include "skyboxcube.h"
#include "../../material/textures/texturemanager.h"

bool SkyboxCube::initialize(char* filename){
	
	int flags = Texture::CLAMP_TO_EDGE;
	flags |= Texture::LINEAR_MIPMAP_LINEAR;
	flags |= Texture::MIPMAP_SGI;
	flags |= Texture::COMPRESSION_ARB;
	
/*	posx = TEXTUREMANAGER::getInstance().load("hotel_posx.tga", texture::TEXTURE_2D, texture::RGB, texture::RGB8, flags);
	posy = TEXTUREMANAGER::getInstance().load("hotel_posy.tga", texture::TEXTURE_2D, texture::RGB, texture::RGB8, flags);
	posz = TEXTUREMANAGER::getInstance().load("hotel_posz.tga", texture::TEXTURE_2D, texture::RGB, texture::RGB8, flags);

	negx = TEXTUREMANAGER::getInstance().load("hotel_negx.tga", texture::TEXTURE_2D, texture::RGB, texture::RGB8, flags);
	negy = TEXTUREMANAGER::getInstance().load("hotel_negy.tga", texture::TEXTURE_2D, texture::RGB, texture::RGB8, flags);
	negz = TEXTUREMANAGER::getInstance().load("hotel_negz.tga", texture::TEXTURE_2D, texture::RGB, texture::RGB8, flags);
*/		
	return true;
}

void SkyboxCube::draw(){

	glPushMatrix();

	negx->bind();
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(-128,  128, -128);

		glTexCoord2f(1,0);
		glVertex3f(-128,  128,  128);

		glTexCoord2f(1,1);
		glVertex3f(-128, -128,  128);

		glTexCoord2f(0,1);
		glVertex3f(-128, -128, -128);
	glEnd();
	negx->unbind();
	
	posx->bind();
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f( 128,  128,  128);

		glTexCoord2f(1,0);
		glVertex3f( 128,  128, -128);

		glTexCoord2f(1,1);
		glVertex3f( 128, -128, -128);

		glTexCoord2f(0,1);
		glVertex3f( 128, -128,  128);
	glEnd();
	posx->unbind();
	
	negy->bind();
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(-128, -128,  128);

		glTexCoord2f(1,0);
		glVertex3f( 128, -128,  128);

		glTexCoord2f(1,1);
		glVertex3f( 128, -128, -128);

		glTexCoord2f(0,1);
		glVertex3f(-128, -128, -128);
	glEnd();
	negy->unbind();
	
	posy->bind();
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(-128,  128, -128);

		glTexCoord2f(1,0);
		glVertex3f( 128,  128, -128);

		glTexCoord2f(1,1);
		glVertex3f( 128,  128,  128);

		glTexCoord2f(0,1);
		glVertex3f(-128,  128,  128);
	glEnd();
	posy->unbind();
	
	posz->bind();
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(-128,  128,  128);

		glTexCoord2f(1,0);
		glVertex3f( 128,  128,  128);

		glTexCoord2f(1,1);
		glVertex3f( 128, -128,  128);

		glTexCoord2f(0,1);
		glVertex3f(-128, -128,  128);
	glEnd();
	posz->unbind();
	
	negz->bind();
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f( 128,  128, -128);

		glTexCoord2f(1,0);
		glVertex3f(-128,  128, -128);

		glTexCoord2f(1,1);
		glVertex3f(-128, -128, -128);

		glTexCoord2f(0,1);
		glVertex3f( 128, -128, -128);
	glEnd();
	negz->unbind();

	glPopMatrix();

}
