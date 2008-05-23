#ifndef NODE_H_
#define NODE_H_

#include <dae.h>
#include <dom/domMaterial.h>
#include <dom/domGeometry.h>
#include <dom/domNode.h>
#include <dom/domCOLLADA.h>
#include <vector>
#include <list>

#include "Mesh.h"

enum{
	DAE_FILE_NOT_FOUND = -1
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
