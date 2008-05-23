#ifndef MESH_H_
#define MESH_H_

#include <list>
#include "Material.h"

struct Triangles{
	unsigned int count;
	unsigned int* triangles;
	float* vertices;
	unsigned int verticesCount;
	Material* material;
};

class Mesh {
public:

	Mesh(){};
	Mesh(domMesh* meshTag);
	
	std::list<Triangles*> tris;

};

#endif /*MESH_H_*/
