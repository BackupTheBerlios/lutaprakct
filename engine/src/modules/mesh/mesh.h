#ifndef _MESH_H_
#define _MESH_H_

#include "../../util/math/algebra.h"
#include "meshData.h"
#include "meshRenderer.h"
#include <string>

class Mesh{
	
public:

	Mesh();
	Mesh(std::string filename);
	virtual ~Mesh();
	
	bool initialize(std::string filename);
	
	//as funcoes abaixo modificam a matriz do objeto
	void rotate(float angle, float x, float y, float z);
	void rotate(float angle, vec3 axis);
	
	void translateAdd(float x, float y, float z );
	void translateTo(float amount, vec3 axis);
	void translateTo(float x, float y, float z);
	
	void scale(float x, float y, float z);
	void scaleAdd(float x, float y, float z);

	vec3 getPosition();
	vec3 getScale();

private:

	MeshData* meshdata;
	MeshRenderer* renderer;
	mat4 modelview;
	
};


#endif //_MESH_H_
