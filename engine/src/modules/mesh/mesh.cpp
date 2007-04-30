
#include "mesh.h"
#include "meshManager.h"
#include "meshrenderer/meshRenderer.h"
#include <GL/gl.h>
#include <cmath>

#include <iostream>

Mesh::Mesh(){
	identity(modelview);
}

Mesh::Mesh(std::string filename, int flags){
	initialize(filename, flags);
}

Mesh::~Mesh(){
}

bool Mesh::initialize(std::string filename, int flags){
	
	identity(modelview);
	meshdata = MESHMANAGER::getInstance().load( const_cast<char*>(filename.c_str()) );
	
	int rendertype = discoverRenderType();
	if (rendertype)
		renderer = getMeshRenderer(rendertype);
	else
		return false;
	
	time = 0.0;
	return true;	
}

//angulo em graus
void Mesh::rotate(float angle, vec3 axis){
	
	mat4 mat;
	identity(mat);
		
	float rad = degtorad(angle);
	float c = cos(rad);
	float s = sin(rad);
	vec3 v = axis;
	normalize(v);
	float xx = v.x * v.x;
	float yy = v.y * v.y;
	float zz = v.z * v.z;
	float xy = v.x * v.y;
	float yz = v.y * v.z;
	float zx = v.z * v.x;
	float xs = v.x * s;
	float ys = v.y * s;
	float zs = v.z * s;
	mat[0] = (1.0f - c) * xx + c; mat[4] = (1.0f - c) * xy - zs; mat[8] = (1.0f - c) * zx + ys; mat[12] = 0.0;
	mat[1] = (1.0f - c) * xy + zs; mat[5] = (1.0f - c) * yy + c; mat[9] = (1.0f - c) * yz - xs; mat[13] = 0.0;
	mat[2] = (1.0f - c) * zx - ys; mat[6] = (1.0f - c) * yz + xs; mat[10] = (1.0f - c) * zz + c; mat[14] = 0.0;
	mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
	
	modelview = modelview*mat;
}

void Mesh::rotate(float angle, float x, float y, float z){
	
	mat4 mat;
	identity(mat);
		
	float rad = degtorad(angle);
	float c = cos(rad);
	float s = sin(rad);
	vec3 v(x, y, z);
	normalize(v);
	float xx = v.x * v.x;
	float yy = v.y * v.y;
	float zz = v.z * v.z;
	float xy = v.x * v.y;
	float yz = v.y * v.z;
	float zx = v.z * v.x;
	float xs = v.x * s;
	float ys = v.y * s;
	float zs = v.z * s;
	mat[0] = (1.0f - c) * xx + c; mat[4] = (1.0f - c) * xy - zs; mat[8] = (1.0f - c) * zx + ys; mat[12] = 0.0;
	mat[1] = (1.0f - c) * xy + zs; mat[5] = (1.0f - c) * yy + c; mat[9] = (1.0f - c) * yz - xs; mat[13] = 0.0;
	mat[2] = (1.0f - c) * zx - ys; mat[6] = (1.0f - c) * yz + xs; mat[10] = (1.0f - c) * zz + c; mat[14] = 0.0;
	mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
	
	modelview = modelview*mat;
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

	modelview[12] = x;
	modelview[13] = y;
	modelview[14] = z;
}

void Mesh::translateTo(float amount, vec3 axis){
	
	modelview[12] = axis.x;
	modelview[13] = axis.y;
	modelview[14] = axis.z;
	
}

void Mesh::translateAdd(float x, float y, float z){
	
	modelview[12] = modelview[12] + x;
	modelview[13] = modelview[13] + y;
	modelview[14] = modelview[14] + z;
	
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

void Mesh::draw(){
	glPushMatrix();
	glMultMatrixf(modelview.mat_array);
	renderer->draw(meshdata);
	glPopMatrix();
}

void Mesh::draw(int frame){
	glPushMatrix();
	glMultMatrixf(modelview.mat_array);
	renderer->draw(meshdata, frame);
	glPopMatrix();
}

void Mesh::draw(float elapsedTime, int startFrame, int endFrame){
	glPushMatrix();
	glMultMatrixf(modelview.mat_array);
	renderer->draw(meshdata, elapsedTime, startFrame, endFrame);
	glPopMatrix();
}

void Mesh::update(float elapsedTime){

	time += elapsedTime;
//teste pro objeto se mover
//	translateAdd(elapsedTime*3, 0.0, 0.0);
	
}

int Mesh::discoverRenderType(){

	int meshtype = meshdata->getMeshType();
	
	if (meshtype == MD2MESH)
		return MD2RENDERER;
	else if (meshtype == OBJMESH)
		return OBJRENDERER;
	else
		return 0;

}
