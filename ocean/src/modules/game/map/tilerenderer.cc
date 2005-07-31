
#include "tilerenderer.h"

tileRenderer::tileRenderer(){
}

tileRenderer::~tileRenderer(){
}


unsigned char tileRenderer::addTile(tile Tile){
	tiles.push_back(Tile);
	return tiles.size();
}

void  tileRenderer::renderTile (unsigned char id, int x, int y, SDL_Surface *dest){
    
    tiles[id - 1].render(dest, x, y);
}
