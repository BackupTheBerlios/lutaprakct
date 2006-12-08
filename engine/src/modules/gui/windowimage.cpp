
#include "windowimage.h"
#include <iostream>

void WindowImage::shutdown(){
}

bool WindowImage::initialize(int height, int width, int x, int y, bool useAlpha){
	
	this->width = width;
	this->height = height;
	position[0] = x;
	position[1] = y;
	color[0] = color[1] = color[2] = color[3] = 1.0;
	color[3] = 0.5;
	tex = NULL;
	bordersize = 0;
	alpha = useAlpha;	
	toptex = bottomtex = righttex = lefttex = toprightex = toplefttex = bottomrighttex = bottomlefttex = NULL;

	return true;
}

void WindowImage::setTexture(std::string filename){
	
	int format;
	if (alpha)
		format = texture::RGBA;
	else
		format = texture::RGB;
	
	tex = TEXTUREMANAGER::getInstance().load( const_cast<char*>(filename.c_str()), texture::TEXTURE_2D, format, texture::RGB8, 0);
	
}

void WindowImage::setBorder(std::string toptexfile, std::string bottomtexfile, std::string righttexfile, std::string lefttexfile, std::string toprightexfile, std::string toplefttexfile, std::string bottomrighttexfile, std::string bottomlefttexfile, int bordersize){

	int format;
	if (alpha)
		format = texture::RGBA;
	else
		format = texture::RGB;
		
	toptex = TEXTUREMANAGER::getInstance().load( const_cast<char*>(toptexfile.c_str()), texture::TEXTURE_RECTANGLE, format, texture::RGB8, 0);
	bottomtex = TEXTUREMANAGER::getInstance().load( const_cast<char*>(bottomtexfile.c_str()), texture::TEXTURE_RECTANGLE, format, texture::RGB8, 0);
	righttex = TEXTUREMANAGER::getInstance().load( const_cast<char*>(righttexfile.c_str()), texture::TEXTURE_RECTANGLE, format, texture::RGB8, 0);
	lefttex = TEXTUREMANAGER::getInstance().load( const_cast<char*>(lefttexfile.c_str()), texture::TEXTURE_RECTANGLE, format, texture::RGB8, 0);
	toprightex = TEXTUREMANAGER::getInstance().load( const_cast<char*>(toprightexfile.c_str()), texture::TEXTURE_RECTANGLE, format, texture::RGB8, 0);
	toplefttex = TEXTUREMANAGER::getInstance().load( const_cast<char*>(toplefttexfile.c_str()), texture::TEXTURE_RECTANGLE, format, texture::RGB8, 0);
	bottomrighttex = TEXTUREMANAGER::getInstance().load( const_cast<char*>(bottomrighttexfile.c_str()), texture::TEXTURE_RECTANGLE, format, texture::RGB8, 0);
	bottomlefttex = TEXTUREMANAGER::getInstance().load( const_cast<char*>(bottomlefttexfile.c_str()), texture::TEXTURE_RECTANGLE, format, texture::RGB8, 0);
	
	this->bordersize = bordersize;
	
}

void WindowImage::draw(){
	
	glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();	
	
	glColor4fv(color);
	
	if (alpha){
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_BLEND); 
	}
	
	if (tex)
		tex->bind();
	
	glTranslated(position[0], position[1], position[2]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(0, height);
		
		glTexCoord2f(1.0f, 0.0f);	
		glVertex2i(width, height);
		
		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(width, 0);
		
		glTexCoord2f(0.0f , 1.0f);	
		glVertex2i(0, 0);
	glEnd();

	if (tex)
		tex->unbind();
	
	if (bordersize){
		drawBorder();
	}	
	
	if (alpha)
		glDisable(GL_BLEND);
	glPopMatrix();
	glPopAttrib();
	
}

void WindowImage::drawBorder(){
	//borda de baixo
	if (bottomtex)
		bottomtex->bind();
		
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(0, height+bordersize);
	
		glTexCoord2f(bottomtex->getWidth(), 0);	
		glVertex2i(width, height+bordersize);
		
		glTexCoord2f(bottomtex->getWidth(), bottomtex->getHeight());
		glVertex2i(width, height);
		
		glTexCoord2f(0.0f ,bottomtex->getHeight());	
		glVertex2i(0, height);
	glEnd();		
	
	if (bottomtex)
		bottomtex->unbind();
		
	//borda de cima
	if (toptex)
		toptex->bind();
		
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(0, 0);
		
		glTexCoord2f(toptex->getWidth(), 0);	
		glVertex2i(width, 0);
		
		glTexCoord2f(toptex->getWidth(), toptex->getHeight());
		glVertex2i(width, 0-bordersize);
		
		glTexCoord2f(0.0f , toptex->getHeight());	
		glVertex2i(0, 0-bordersize);
	glEnd();
	
	if (toptex)
		toptex->unbind();
		
	if (righttex)
		righttex->bind();
		
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(width, height);
		
		glTexCoord2f( righttex->getWidth(), 0.0f );	
		glVertex2i(width+bordersize, height);
		
		glTexCoord2f(righttex->getWidth(), righttex->getHeight());
		glVertex2i(width+bordersize, 0);
		
		glTexCoord2f(0.0f , righttex->getHeight());
		glVertex2i(width, 0);
	glEnd();
	
	if (righttex)
		righttex->unbind();	
		
	if (lefttex)
		lefttex->bind();
		
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(0-bordersize, height);
		
		glTexCoord2f(lefttex->getWidth(), 0.0f);	
		glVertex2i(0, height);
		
		glTexCoord2f(lefttex->getWidth(), lefttex->getHeight());
		glVertex2i(0, 0);
		
		glTexCoord2f(0.0f , lefttex->getHeight());
		glVertex2i(0-bordersize, 0);
	glEnd();
	
	if (lefttex)
		lefttex->unbind();	
		

	if (toprightex)
		toprightex->bind();
		
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(width, 0);
		
		glTexCoord2f(toprightex->getWidth(), 0.0f);
		glVertex2i(width+bordersize, 0);	
		
		glTexCoord2f(toprightex->getWidth(), toprightex->getHeight());
		glVertex2i(width+bordersize, 0-bordersize);
		
		glTexCoord2f(0.0f , toprightex->getHeight());
		glVertex2i(width, 0-bordersize);
	glEnd();
	
	if (toprightex)
		toprightex->unbind();	
		
	if (toplefttex)
		toplefttex->bind();
		
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(0-bordersize, 0);
		
		glTexCoord2f(toplefttex->getWidth(), 0.0f);
		glVertex2i(0, 0);
		
		glTexCoord2f(toplefttex->getWidth(), toprightex->getHeight());
		glVertex2i(0, 0-bordersize);
		
		glTexCoord2f(0.0f , toplefttex->getHeight());
		glVertex2i(0-bordersize, 0-bordersize);
	glEnd();
	
	if (toplefttex)
		toplefttex->unbind();
		
	if (bottomrighttex)
		bottomrighttex->bind();
		
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(width, height+bordersize);
		
		glTexCoord2f(bottomrighttex->getWidth(), 0.0f);
		glVertex2i(width+bordersize, height+bordersize);
		
		glTexCoord2f(bottomrighttex->getWidth(), bottomrighttex->getHeight());
		glVertex2i(width+bordersize, height);
		
		glTexCoord2f(0.0f , bottomrighttex->getHeight());
		glVertex2i(width, height);
	glEnd();
	
	if (bottomrighttex)
		bottomrighttex->unbind();
		
	if (bottomlefttex)
		bottomlefttex->bind();
		
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(0-bordersize, height+bordersize);
		
		glTexCoord2f(bottomlefttex->getWidth(), 0.0f);
		glVertex2i(0, height+bordersize);
		
		glTexCoord2f(bottomlefttex->getWidth(), bottomlefttex->getHeight());
		glVertex2i(0, height);
		
		glTexCoord2f(0.0f , bottomlefttex->getHeight());
		glVertex2i(0-bordersize, height);
	glEnd();
	
	if (bottomlefttex)
		bottomlefttex->unbind();
}
