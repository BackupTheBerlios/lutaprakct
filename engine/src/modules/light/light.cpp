
#include "light.h"
#include <GL/gl.h>

bool Light::initialize(unsigned int id){
	this->id = id;
	
	glLightfv(GL_LIGHT0+id, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0+id, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0+id, GL_POSITION, position);
	
	return true;
}

Light::Light(){
}

Light::~Light(){
}

void Light::bind(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0+id);
}

void Light::unbind(){
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0+id);
}

void Light::shutdown(){
}
