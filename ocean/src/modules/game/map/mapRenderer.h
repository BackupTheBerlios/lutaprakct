#ifndef _WORLDRENDERER_H_
#define _WORLDRENDERER_H_

#include "map.h"
#include "tilerenderer.h"
#include <SDL/SDL.h>

class mapRenderer{
	
public:

	mapRenderer();
	~mapRenderer();
    
	void renderMap (world *World, int x, int y, SDL_Surface *dest);
	void setTileRenderer (tileRenderer *renderer);
	void setTileSpacing (int h, int v) { hSpacing = h; vSpacing = v; }
   
private:

	tileRenderer *mtileRenderer;
	int hSpacing;
	int vSpacing;
};

#endif //_WORLDRENDERER_H_
