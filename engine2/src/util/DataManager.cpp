#include <iostream>
#include "DataManager.h"
#include "../util/glhelper/Texture.h"

DataManager::DataManager(){
};

DataManager::~DataManager(){
	unloadAll();
}

void* DataManager::loadImage(std::string filename, int target, int format, int internalFormat, int flags){

	std::map<std::string, DataReference>::iterator iter = data.find(filename);
	//se nao tiver a textura, entao carrega e adiciona no map
	if ( iter == data.end()){
		flags |= textureFlags;
		Texture *tex = new Texture(filename, target, format, internalFormat, flags);
		DataReference newData;
		newData.counter = 1;
		newData.data = (void*) tex;
		newData.type = TextureDataType; 
		data[filename] = newData;
		return newData.data;
	}
	else{
		(*iter).second.counter++;
		return (*iter).second.data;
	}
	
}

bool DataManager::unload(std::string filename){
	std::map<std::string, DataReference>::iterator iter = data.find(filename);
	if ( iter == data.end() )
		return false;
	else{
		(*iter).second.counter--;
		if ( (*iter).second.counter <= 0 ){
			if ( (*iter).second.type == TextureDataType )
				delete ((Texture*) (*iter).second.data);
			data.erase(filename);	
		}
	}
	return true;
}

//TODO checar se eh textura
bool DataManager::unloadAll(){
	
	 std::map<std::string, DataReference>::iterator iter;
	 
	 for( iter = data.begin(); iter != data.end(); iter++){
		if ( (*iter).second.type == TextureDataType )
			delete ((Texture*) (*iter).second.data);
	 }
	 data.clear();
	 
	 return true;
}

//TODO fazer ser possivel ler outros alem de collada
void* DataManager::loadMesh(std::string filename){
/*	std::map<std::string, DataReference>::iterator iter = data.find(filename);
	//se nao tiver a textura, entao carrega e adiciona no map
	if ( iter == data.end()){
		DataReference newData;
		newData.counter = 1;
		MeshIO *mesh = new MeshIO(filename.c_str());
		newData.data = (void*) mesh;
		newData.type = MeshDataType; 
		data[filename] = newData;
		return newData.data;
	}
	else{
		(*iter).second.counter++;
		return (*iter).second.data;
	}*/	
}
 

