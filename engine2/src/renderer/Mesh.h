#ifndef MESH_H_
#define MESH_H_

#include <map>
#include <list>
#include <cfxEffect.h>
#include <cfxMaterial.h>

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
	
	cfxMaterial* material;
	std::string materialName;
	
	//IDS dos VBOs
	unsigned int vertexID;
	unsigned int normalID;
	unsigned int indicesID;
};


class Mesh {
public:

	Mesh(){};
	Mesh(domMesh* meshTag, std::map<std::string, cfxMaterial*>*);
	
	std::list<Triangles*> tris;

	void createVBO();
	void destroyVBO();
	void render();
	void bindMaterial(Triangles* tri);
	
};

#endif /*MESH_H_*/
