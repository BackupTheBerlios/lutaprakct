#ifndef _TILE_H_
#define _TILE_H_

#include <SDL/SDL.h>

class tile{
	
public:

	tile();
	~tile();
    
	void setTileSurface (SDL_Surface *tile) { tileSurface = tile; }
	void setTileRect (SDL_Rect rect) { tileRect = rect; }
	void setOffset (int h, int v) { hOffset = h, vOffset = v; }
        
	void render (SDL_Surface *dest, int x, int y);

private:

	SDL_Surface *tileSurface;
	SDL_Rect tileRect;
	int hOffset;
	int vOffset;
};

#endif //_TILE_H_
