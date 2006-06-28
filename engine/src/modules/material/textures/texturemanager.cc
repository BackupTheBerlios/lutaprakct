#include "texturemanager.h"
#include <iostream>
 
texture* textureManager::load(char *name, int target, int format, int internalformat, int flags){
  
	//cria o iterator para o map e procura pelo nome da textura
	std::map<std::string, texture*>::iterator iter = ids.find(name);
	//se nao tiver a textura, entao carrega e adiciona no map
	if ( iter == ids.end()){
		flags |= this->flags;
		texture *tex = new texture(name, target, format, internalformat, flags); 
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

void textureManager::setDefaultFlags(int flags){

	flags = texture::LINEAR_MIPMAP_LINEAR ;
	flags |= texture::MIPMAP_SGI;
	flags |= texture::COMPRESSION_ARB;
	
}
