#ifndef _MESH_H_
#define _MESH_H_

#include "../../util/math/algebra.h"

class Mesh{
	
public:

	Mesh();
	virtual ~Mesh();
	
	void rotate();
	
	void translateAdd(float x, float y, float z );
	void translateTo(float amount, vec3 axis);
	void translateTo(float x, float y, float z);
	
	void scale(float x, float y, float z);
	void scaleAdd(float x, float y, float z);

	vec3 getPosition();
	vec3 getScale();

private:

	mat4 modelview;
	
};


#endif //_MESH_H_
