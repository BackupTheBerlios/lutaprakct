#include "texturemanager.h"
 
texture* textureManager::load(char *name, int target, int flags){
  
	//cria o iterator para o map e procura pelo nome da textura
	std::map<std::string, texture*>::iterator iter = ids.find(name);
	//se nao tiver a textura, entao carrega e adiciona no map
	if ( iter == ids.end()){
		texture *tex = new texture(name, target, flags); 
		ids[name] = tex;
		return tex;
	}
	else{
		return (*iter).second;
	}
}



/*
void CtextureManager::free(int id){

	std::map<std::string, int>::iterator iter;
	for ( iter = manager->ids.begin(); iter != (manager->ids).end(); iter++){
		if (id == (*iter).second){
			glDeleteTextures (1, (GLuint*) (*iter).second);
			manager->ids.erase(iter);
		}
	}
 
}
*/
void textureManager::freeAll(){

	 std::map<std::string, texture*>::iterator iter;
	 
	 for( iter = ids.begin(); iter != ids.end(); iter++){
		(*iter).second->unload();
		 delete (*iter).second;
	 }
	 ids.clear();
}
