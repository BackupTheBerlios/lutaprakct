#ifndef SCENE_H_
#define SCENE_H_

#include <dae.h>
#include <dom/domMaterial.h>
#include <dom/domGeometry.h>
#include <dom/domNode.h>
#include <dom/domCOLLADA.h>
#include "Node.h"
#include "Mesh.h"
#include <map>
#include <string>

enum{
	DAE_FILE_NOT_FOUND = -1
};

class Scene{
	
public:
	
	int initialize(char* filename);
	
	void readLibraryLights();
	void readLibraryMaterials();
	void readLibraryGeometries(domLibrary_geometries* lib);
	
	void readGeometry(domGeometry* geo);
	
	std::list<Node*> nodes;
	
	std::map<std::string, Mesh*> instancedMeshes;
	
};

#endif /*SCENE_H_*/
