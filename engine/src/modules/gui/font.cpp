
#include "font.h"
#include <GL/gl.h>
#include	 <stdarg.h>	

Font::Font(){
	fontTexture = NULL;
}

Font::Font(std::string filename){
	fontTexture = NULL;
	initialize(filename);
}

Font::~Font(){
	shutdown();
}

bool Font::initialize(std::string filename){

	fontTexture = TEXTUREMANAGER::getInstance().load( const_cast<char*>(filename.c_str()), texture::TEXTURE_2D, texture::RGB, texture::RGB8, 0);

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

void Font::print(int x, int y, int set, const char *fmt, ...){
	
	char	text[1024];
	va_list	ap;	

	if (fmt == NULL)		
		return;	

	va_start(ap, fmt);		
	    vsprintf(text, fmt, ap);		
	va_end(ap);				

	if (set > 1)
		set = 1;	

	glEnable(GL_TEXTURE_2D);	
	glLoadIdentity();//necessario isso?
	glTranslated(x, y, 0);
	glListBase(listID - 32 + (128 * set));

	glScalef(1.0f, 2.0f, 1.0f);

	glCallLists( strlen(text), GL_UNSIGNED_BYTE, text);	
	glDisable(GL_TEXTURE_2D);
}

