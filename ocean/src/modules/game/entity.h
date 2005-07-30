#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "../sprites/sprite.h"
#include <string>

/** entidade eh algo que existe in game, os players, os npcs e os itens sao entity
 */

class entity{
	
public:

	entity(std::string filename);
	~entity();
	
	void setx(long int x);
	void sety(long int y);
	
	void draw();
	
private:

	long int x, y;
    sprite img;
    
	std::string filename;
	
};

#endif //_ENTITY_H_
