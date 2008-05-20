
#include "VertexLight.h"
#include <GL/gl.h>

bool VertexLight::initialize(unsigned int id){
	this->id = id;
	
	glLightfv(GL_LIGHT0+id, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0+id, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0+id, GL_POSITION, position);
	
	return true;
}

VertexLight::VertexLight(){
}

VertexLight::~VertexLight(){
}

void VertexLight::bind(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0+id);
}

void VertexLight::unbind(){
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0+id);
}

void VertexLight::shutdown(){
}
