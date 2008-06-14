
#include "Scene.h"
#include "Cg.h"
#include <cfxLoader.h>

int Scene::initialize(char* filename){
	
	root = NULL;
	DAE dae;
	domCOLLADA* root = dae.open(filename);
	if (!root)
		return DAE_FILE_NOT_FOUND;
	
	//primeiro ler as libs
	domLibrary_geometries_Array geometry_array = root->getLibrary_geometries_array();
	for (size_t i = 0; i < geometry_array.getCount(); i++){
		readLibraryGeometries(geometry_array[i]);
	}
	
	domLibrary_lights_Array light_array = root->getLibrary_lights_array();
	for (size_t i = 0; i < light_array.getCount(); i++) {
		readLibraryLights(light_array[i]);
	}
	
	readCfxMaterials(filename);
	
	//TODO ler as varias scenes
	domVisual_scene* visualScene = daeSafeCast<domVisual_scene>(root->getDescendant("visual_scene"));
	
	domNode_Array& nodes = visualScene->getNode_array(); //todos os nodes da scena
	for (size_t i = 0; i < nodes.getCount(); i++){
		Node* n = new Node(*nodes[i], &sceneData);
		this->nodes.push_back(n);
	}
	
	return 0;
}

void Scene::render(){
	
	std::list<Node*>::iterator iter;
	for (iter = nodes.begin(); iter != nodes.end(); iter++){
		(*iter)->render();
	}
	
}

void Scene::readLibraryGeometries(domLibrary_geometries* lib){
	
	domGeometry_Array geoArray = lib->getGeometry_array();
	for (size_t i = 0; i < geoArray.getCount(); i++ )
		readGeometry(geoArray[i]);
	
}

void Scene::readGeometry(domGeometry* geo){
	
	//cada tag geometry tem apenas uma tag <mesh> ou <spline> so nos interessa a <mesh>
	if (geo->getMesh()){ //se tem <mesh>
		Mesh* m = new Mesh(geo->getMesh(), & (sceneData.cfxMaterials));
		sceneData.instancedMeshes[geo->getID()].push_back(m);
	}
	
}

void Scene::readLibraryLights(domLibrary_lights* lib ){
	domLight_Array lightArray = lib->getLight_array();
	for(size_t i = 0; i < lightArray.getCount(); i++){
		Light* l = new Light(lightArray[i]);
		lights.push_back(l);
	}
}

void Scene::readCfxMaterials(std::string filename){
	
	cfxLoader::loadMaterialsAndEffectsFromFile(filename, sceneData.cfxMaterials, sceneData.cfxEffects, CG::getInstance().cgContext);
	
}


