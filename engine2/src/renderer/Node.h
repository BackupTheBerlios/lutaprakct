#ifndef NODE_H_
#define NODE_H_

#include <dae.h>
#include <dom/domMaterial.h>
#include <dom/domGeometry.h>
#include <dom/domNode.h>
#include <dom/domCOLLADA.h>
#include <vector>
#include <list>

enum{
	DAE_FILE_NOT_FOUND = -1
};

class Material {
public:
	std::vector<float> diffuseColor;
	char* diffuseTexture;
	// ... and lots of other parameters
	
	Material(domMaterial& mtl) {
		// Grab the <effect> from the <material> and initalize the parameters
	}
};

struct Triangles{
	unsigned int count;
	unsigned int* triangles;
	Material* material;
};

class Mesh {
public:

	std::list<Triangles*> tris;

};

class Node{

public:
	
	std::list<Mesh*> meshes;
	std::list<Node*> childNodes;

	Node(){};
	Node(domNode& node);
};

class Scene{
	
public:
	
	int initialize(char* filename);
	
	std::list<Node*> nodes;
	
};

void initializeNode();

#endif /*NODE_H_*/
