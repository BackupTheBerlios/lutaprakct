#ifndef MESH_H_
#define MESH_H_

#include <list>
#include "Material.h"

struct TexCoord{
	unsigned int count;
	unsigned int set;
	float* texCoords;
};

struct Triangles{
	
	unsigned int count;
	unsigned int* triangles;
	
	float* vertices;
	unsigned int verticesCount;
	
	float* normals;
	unsigned int normalsCount;
	
	std::list<TexCoord*> texCoords;
	
	Material* material;
};

class Mesh {
public:

	Mesh(){};
	Mesh(domMesh* meshTag);
	
	std::list<Triangles*> tris;

};

#endif /*MESH_H_*/
