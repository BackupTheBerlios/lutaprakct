#include "camera.h"
#include <cmath>
#include <GL/gl.h>

#include <iostream>

camera::camera(){
	identity(modelview);
    time = 0.0f;
}

camera::~camera(){
}

/* move em x unidades a camera no eixo axis.
 * o processo eh so criar a matriz de translacao com o axis e multiplicar pela modelview
 * matriz de translacao tem o formato:
 * |m0 m4 m8    x|
 * |m1 m5 m9    y|
 * |m2 m6 m10   z|
 * |m3 m7 m11 m15|
 */
void camera::move(float x, vec3 axis){

	x *= time;
	
	mat4 translation;
	identity(translation);
	axis = (-x)*axis;
	
	translation[12] = axis.x;
	translation[13] = axis.y;
	translation[14] = axis.z;
	
	modelview = modelview*translation;
		
}

void camera::rotate(float angle, vec3 axis){
	
	angle *= time;
	
	quat rotation, rotationConjugate;
	angle = degtorad(angle);
	
	rotation = axisToQuaternion(angle, axis);
	rotationConjugate = conjugate(rotation);
	
	quat quatX(1.0, 0.0, 0.0, 0.0),
	     quatY(0.0, 1.0, 0.0, 0.0),
	     quatZ(0.0, 0.0, 1.0, 0.0);
	
	quatX = rotation * quatX * rotationConjugate;
	quatY = rotation * quatY * rotationConjugate;
	quatZ = rotation * quatZ * rotationConjugate;
	
	mat4 matrix;
	
	identity(matrix);
	
	matrix[0] = quatX.x;
	matrix[4] = quatX.y;
	matrix[8] = quatX.z;
	
	matrix[1] = quatY.x;
	matrix[5] = quatY.y;
	matrix[9] = quatY.z;
	
	matrix[2] = quatZ.x;
	matrix[6] = quatZ.y;
	matrix[10] = quatZ.z;
	
	modelview = modelview * matrix;
	
}

void camera::update(float time){

	this->time = time;
	glLoadMatrixf(modelview.mat_array);
	
}

vec3 camera::getPosition(){
	return vec3(modelview[12], modelview[13], modelview[14]);
}

void camera::handleEvent(const event &e){

	switch (e.type){
		case E_MOUSE_ROTATE_X: rotate(e.arg1, vec3(0.0, 1.0, 0.0)); break;
		case E_MOUSE_ROTATE_Y: rotate(e.arg1, vec3(1.0, 0.0, 0.0)); break;
		case E_KEY_UP:         move(10.0f, vec3(0.0, 0.0, (-1.0))); break;
	    case E_KEY_DOWN:       move(10.0f, vec3(0.0, 0.0, 1.0)); break;
	    case E_KEY_LEFT:       move(10.0f, vec3((-1.0), 0.0, 0.0)); break;
	    case E_KEY_RIGHT:      move(10.0f, vec3(1.0, 0.0, 0.0)); break;
	}	
	
}
