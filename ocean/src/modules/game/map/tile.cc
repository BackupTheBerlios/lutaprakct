
#include "tile.h"

tile::tile(): tileSurface (NULL)
{
}

tile::~tile()
{
}

void  tile::render(SDL_Surface *dest, int x, int y){

    SDL_Rect dstRect = {x + hOffset, y + vOffset, 0, 0};
    SDL_BlitSurface(tileSurface, &tileRect, dest, &dstRect);
}
