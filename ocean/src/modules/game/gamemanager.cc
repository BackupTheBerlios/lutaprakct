#include "gamemanager.h"
#include "../sprites/spriteManager.h"

bool gameManager::initialize(){
	return true;
}

void gameManager::shutdown(){
}

/* simplesmente adiciona o entity na lista
 */
bool gameManager::addEntity(std::string filename, long int x, long int y){
	
	entity *newentity = new entity(filename);
	newentity->setx(x);
	newentity->sety(y);
	entidades.push_back(newentity);
	
}	

/** loop na lista para desenhar cada entidade
 * TODO desenhar o mapa antes e verificar o que esta visivel na tela
 * para so entao desenhar
 */
void gameManager::draw(){
	
	std::list<entity*>::iterator iter;
	
	for (iter = entidades.begin(); iter != entidades.end(); iter++){
		(*iter)->draw();
	}
	
	
}