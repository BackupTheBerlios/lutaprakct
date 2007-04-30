
#include "font.h"
#include <GL/gl.h>
#include	 <stdarg.h>	

#include <iostream>

Font::Font(){
	fontTexture = NULL;
	fontset = 0;
	color[0] = color[1] = color[2] = color[3] = 1.0;
}

Font::Font(std::string filename){
	fontTexture = NULL;
	fontset = 0;
	color[0] = color[1] = color[2] = color[3] = 1.0;
	initialize(filename);
}

Font::~Font(){
	shutdown();
}

void Font::setColor(float r, float g, float b){
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Font::setColor(float r, float g, float b, float a){
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
}

void Font::setFontSet(int i){
	fontset = i;
}

void Font::setCharacterWidth(float w){
	width = w;
}

void Font::setCharacterHeight(float h){
	height = h;
}

void Font::setScale(float x, float y, float z){
	scale[0] = x;
	scale[1] = y;
	scale[2] = z;
}

bool Font::initialize(std::string& filename){

	fontTexture = TEXTUREMANAGER::getInstance().load( filename, Texture::TEXTURE_2D, Texture::RGBA, Texture::RGB8, 0);

	listID = glGenLists(256);
	fontTexture->bind();
	for (int i = 0; i < 256; i++){
		float cx=float(i%16)/16.0f;
		float cy=float(i/16)/16.0f;

		glNewList(listID + i, GL_COMPILE);
			glBegin(GL_QUADS);//cada quad = um caractere
				glTexCoord2f(cx, 1.0f - cy - 0.0625f);
				glVertex2d(0, 16);
				glTexCoord2f(cx + 0.0625f, 1.0f-cy-0.0625f);	
				glVertex2i(16, 16);
				glTexCoord2f(cx + 0.0625f, 1.0f - cy-0.001f);
				glVertex2i(16, 0);
				glTexCoord2f(cx, 1.0f - cy - 0.001f);	
				glVertex2i(0, 0);
			glEnd();	
			glTranslated(14, 0, 0);
		glEndList();			
	}
	
	fontTexture->unbind();
	
	return true;
}

void Font::shutdown(){
	glDeleteLists(listID, 256);	
}

void Font::print(int x, int y, const char* texto, ...){
	
	char	 text[1024];
	va_list	ap;	

	if (texto == NULL)		
		return;	

	va_start(ap, texto);		
	    vsprintf(text, texto, ap);		
	va_end(ap);	

	glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT);
	glColor4fv(color);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND); 

	glPushMatrix(); 
	glLoadIdentity(); //zera a modelview
	fontTexture->bind(); //ativa a textura da fonte	
	
	glTranslated(x, y, 0); //posiciona o texto da vonte
	glListBase(listID - 32 + (128 * fontset));
	glCallLists( strlen(text), GL_UNSIGNED_BYTE, text);	
	
	fontTexture->unbind();
	glPopAttrib();
	glPopMatrix();
	glDisable(GL_BLEND);
}

