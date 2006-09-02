#include "meshManager.h"
#include <iostream>
 
MeshData* MeshManager::load(char* name){
  
	std::map<std::string, MeshData*>::iterator iter = ids.find(name);
	if ( iter == ids.end()){
		MeshData* meshdata = loadMeshData(name);; 
		//meshdata->initialize(name);
		ids[name] = meshdata;
		return meshdata;
	}
	else{
		return (*iter).second;
	}
}


void MeshManager::freeAll(){

	 std::map<std::string, MeshData*>::iterator iter;
	 
	 for( iter = ids.begin(); iter != ids.end(); iter++){
		(*iter).second->unload();
		 delete (*iter).second;
	 }
	 ids.clear();
}

