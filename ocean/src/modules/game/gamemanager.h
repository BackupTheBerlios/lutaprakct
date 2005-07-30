#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "entity.h"

#include <string>
#include <list>

/* TODO talvez seja bom dividir as entity entre player, npcs e items?
 */

class gameManager{
	
public:

	bool initialize();
	void shutdown();
	
	void draw();
	bool addEntity(std::string filename, long int x, long int y);
	
private:

	std::list<entity*> entidades;
	
};	

#endif //_GAMEMANAGER_H_
