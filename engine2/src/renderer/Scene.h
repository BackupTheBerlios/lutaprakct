#ifndef SCENE_H_
#define SCENE_H_

#include <dae.h>
#include <dom/domMaterial.h>
#include <dom/domGeometry.h>
#include <dom/domNode.h>
#include <dom/domCOLLADA.h>
#include "Node.h"
#include "Mesh.h"
#include "Light.h"
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
	void readLibraryLights(domLibrary_lights* lib);
	
	void readGeometry(domGeometry* geo);
	//void readLight(domLight* light);
	
	std::list<Node*> nodes;
	
	std::map<std::string, std::list<Mesh*> > instancedMeshes;
	
	std::list<Light*> lights;
	
};

#endif /*SCENE_H_*/
