
#include "mesh.h"

Mesh::Mesh(){
	identity(modelview);
}

Mesh::~Mesh(){
}

void Mesh::translateTo(float x, float y, float z){

	mat4 translation;
	identity(translation);
	
	translation[12] = x;
	translation[13] = y;
	translation[14] = z;
	modelview = modelview*translation;
}

void Mesh::translateTo(float amount, vec3 axis){
	
	mat4 translation;
	identity(translation);
	axis = (-amount)*axis;

	translation[12] = axis.x;
	translation[13] = axis.y;
	translation[14] = axis.z;
	modelview = modelview*translation;
	
}

void Mesh::translateAdd(float x, float y, float z){

	mat4 translation;
	identity(translation);
	
	translation[12] = modelview[12] + x;
	translation[13] = modelview[13] + y;
	translation[14] = modelview[14] + z;
	modelview = modelview*translation;
	
}

void Mesh::scale(float x, float y, float z){

	mat4 scale;
	identity(scale);
	
	scale[0] = x;
	scale[5] = y;
	scale[10] = z;
	modelview = modelview*scale;

}

void Mesh::scaleAdd(float x, float y , float z){
	
	mat4 scale;
	identity(scale);
	
	scale[0] = modelview[0] + x;
	scale[5] = modelview[5] + y;
	scale[10] = modelview[10] + z;
	modelview = modelview*scale;	
}

vec3 Mesh::getPosition(){
	 return vec3( modelview[12], modelview[13], modelview[14] );
}

vec3 Mesh::getScale(){
	 return vec3( modelview[0], modelview[5], modelview[10] );
}


