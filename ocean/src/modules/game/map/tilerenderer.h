#ifndef _TILERENDERER_H_
#define _TILERENDERER_H_

#include <SDL/SDL.h>
#include <vector>
#include "tile.h"

class tileRenderer{
	
public:

	tileRenderer();
	~tileRenderer();

	unsigned char addTile (tile Tile);
	void renderTile (unsigned char id, int x, int y, SDL_Surface *dest);    
   
private:

	std::vector<tile> tiles;
};

#endif //_TILERENDERER_H_
