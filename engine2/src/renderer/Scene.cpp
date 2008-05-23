
#include "Scene.h"

int Scene::initialize(char* filename){
	
	DAE dae;
	domCOLLADA* root = dae.open(filename);
	if (!root)
		return DAE_FILE_NOT_FOUND;
	
	//primeiro ler as libs
	domLibrary_geometries_Array geometry_array = root->getLibrary_geometries_array();
	for (size_t i = 0; i < geometry_array.getCount(); i++){
		readLibraryGeometries(geometry_array[i]);
	}
		
	
	//TODO ler as varias scenes
/*	domVisual_scene* visualScene = daeSafeCast<domVisual_scene>(root->getDescendant("visual_scene"));
	
	domNode_Array& nodes = visualScene->getNode_array(); //todos os nodes da scena
	for (size_t i = 0; i < nodes.getCount(); i++){
		Node* n = new Node(*nodes[i]);
		this->nodes.push_back(n);
	}*/
	
	return 0;
}


void Scene::readLibraryGeometries(domLibrary_geometries* lib){
	
	domGeometry_Array geoArray = lib->getGeometry_array();
	for (size_t i = 0; i < geoArray.getCount(); i++ )
		readGeometry(geoArray[i]);
	
}

void Scene::readGeometry(domGeometry* geo){
	
	//cada tag geometry tem apenas uma tag <mesh> ou <spline> so nos interessa a <mesh>
	if (geo->getMesh()){ //se tem <mesh>
		Mesh* m = new Mesh(geo->getMesh());
		instancedMeshes[geo->getID()] = m;
	}
	
}
