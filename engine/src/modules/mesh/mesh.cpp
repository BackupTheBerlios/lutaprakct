
#include "mesh.h"
#include "meshManager.h"

Mesh::Mesh(){
	identity(modelview);
}

Mesh::Mesh(std::string filename){
	identity(modelview);
	initialize(filename);
}

Mesh::~Mesh(){
}

bool Mesh::initialize(std::string filename){

	meshdata = MESHMANAGER::getInstance().load(const_cast<char*>(filename.c_str()));

	return true;	
}

/*  If the translation is defined by the vector [X Y Z ], then the 4x4
  matrix to implement translation is as follows:
        | 1  0  0  X |
        |            |
        | 0  1  0  Y |
    M = |            |
        | 0  0  1  Z |
        |            |
        | 0  0  0  1 |
  If the vector is [0 0 0] then the vertex list will remain as before.*/

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

/*  A scaling matrix is used to enlarge or shrink the size of a 3D model.
  If the scaling vector is [X Y Z] then the matrix to perform this is
  as follows:
        | X  0  0  0 |
        |            |
        | 0  Y  0  0 |
    M = |            |
        | 0  0  Z  0 |
        |            |
        | 0  0  0  1 |
  If the scaling vector is [1 1 1], then this generates the identity
  matrix and vertex geometry will remain unchanged.*/
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


