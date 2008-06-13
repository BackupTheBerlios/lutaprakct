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
	
	//IDS dos VBOs
	unsigned int vertexID;
	unsigned int normalID;
};


class Mesh {
public:

	Mesh(){};
	Mesh(domMesh* meshTag);
	
	std::list<Triangles*> tris;

	void createVBO();
	void destroyVBO();
	void drawVBO();
	void render();
	
};

#endif /*MESH_H_*/
