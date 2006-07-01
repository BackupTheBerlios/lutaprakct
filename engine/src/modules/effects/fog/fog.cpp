
#include "fog.h"

#include<GL/gl.h>
#include<GL/glu.h>

Fog::Fog(float r, float g, float b, float a, float density, float start, float end, int mode){
	setColor(r, g, b, a);
	setDensity(density);
	setStart(start);
	setEnd(end);
	setMode(mode);
}

Fog::~Fog(){
}

void Fog::setColor(float r, float g, float b, float a){
	GLfloat fogColor[4] = { r, g, b, a };
	glFogfv(GL_FOG_COLOR, fogColor);
}

void Fog::setDensity(float density){
	glFogf(GL_FOG_DENSITY, density);
}

void Fog::setStart(float start){
	glFogf(GL_FOG_START, start);
}

void Fog::setEnd(float end){
	glFogf(GL_FOG_END, end);
}

void Fog::setMode( int mode){
	GLint fogMode;
	if (mode == FOG_EXP)
		fogMode = GL_EXP;
	else if (mode == FOG_EXP2)
		fogMode = GL_EXP2;
	else if (mode == FOG_LINEAR )
		fogMode = GL_LINEAR;
		
	glFogi(GL_FOG_MODE, fogMode);
}

void Fog::bind(){
	glEnable(GL_FOG);
}

void Fog::unbind(){
	glDisable(GL_FOG);
}
