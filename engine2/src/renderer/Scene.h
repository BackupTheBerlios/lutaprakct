#ifndef SCENE_H_
#define SCENE_H_

#include <dae.h>
#include <dom/domMaterial.h>
#include <dom/domGeometry.h>
#include <dom/domNode.h>
#include <dom/domCOLLADA.h>
#include <cfxEffect.h>
#include <cfxMaterial.h>
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
	void readLibraryGeometries(domLibrary_geometries* lib);
	void readLibraryLights(domLibrary_lights* lib);
	
	void readLibraryMaterials(domLibrary_materials* lib);
	void readLibraryEffects(domLibrary_effects* lib);
	//esse metodo usa a lib collada_fx e substitui os outros dois acima
	void readCfxMaterials(DAE* dae); 
	
	void readGeometry(domGeometry* geo);
	void readEffect(domEffect* fx);
	
	std::list<Node*> nodes;
	
	std::map<std::string, std::list<Mesh*> > instancedMeshes;
	std::map<std::string, cfxMaterial*>		cfxMaterials;
	std::map<std::string, cfxEffect*>		cfxEffects;
	
	std::list<Light*> lights;
	
};

#endif /*SCENE_H_*/
