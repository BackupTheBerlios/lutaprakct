#include "texturemanager.h"
#include <iostream>
 
Texture* TextureManager::load(std::string& filename, int target, int format, int internalformat, int flags){
  
	//cria o iterator para o map e procura pelo nome da textura
	std::map<std::string, Texture*>::iterator iter = ids.find(filename);
	//se nao tiver a textura, entao carrega e adiciona no map
	if ( iter == ids.end()){
		flags |= this->flags;
		Texture *tex = new Texture(filename, target, format, internalformat, flags); 
		ids[filename] = tex;
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
void TextureManager::freeAll(){

	 std::map<std::string, Texture*>::iterator iter;
	 
	 for( iter = ids.begin(); iter != ids.end(); iter++){
		(*iter).second->unload();
		 delete (*iter).second;
	 }
	 ids.clear();
}

void TextureManager::setDefaultFlags(){

	flags = Texture::LINEAR;
	flags |= Texture::MIPMAP_SGI;
	flags |= Texture::COMPRESSION_ARB;
	
}
