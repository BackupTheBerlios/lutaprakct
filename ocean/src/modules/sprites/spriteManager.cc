
#include "spriteManager.h"


spriteBase* spriteManager::load(std::string name){
  
	//cria o iterator para o map e procura pelo nome da textura
	std::map<std::string, spriteBase*>::iterator iter = baseSprites.find(name);
	//se nao tiver a textura, entao carrega e adiciona no map
	if ( iter == baseSprites.end()){
		spriteBase *sprite = new spriteBase();
		sprite->initialize(name.c_str());
		baseSprites[name] = sprite;
		return sprite;
	}
	else{
		return (*iter).second;
	}
}

void spriteManager::freeAll(){

	 std::map<std::string, spriteBase*>::iterator iter;
	 
	 for( iter = baseSprites.begin(); iter != baseSprites.end(); iter++){
		//(*iter).second->unload();
		 delete (*iter).second;
	 }
	 baseSprites.clear();
}

