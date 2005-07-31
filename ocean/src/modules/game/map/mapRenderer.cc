
#include "mapRenderer.h"
#include "mapCell.h"
#include <vector>

mapRenderer::mapRenderer(): mtileRenderer (NULL){
}

mapRenderer::~mapRenderer(){
}

void mapRenderer::renderMap(world *World, int cameraX, int cameraY, SDL_Surface *dest){

    
    const mapCell *cell;
	
	// Offsets of the top left tile
	int offsetX, offsetY;
	offsetX = cameraX % (hSpacing * 2) + (hSpacing * 2);
	offsetY = cameraY % (vSpacing * 2) + (vSpacing * 2);
	
	// Map coordinates of the top left tile
	int mapX, mapY, tmpMapX, tmpMapY;
	tmpMapX = mapX = (cameraX / (hSpacing * 2)) + (cameraY / (vSpacing * 2));
	tmpMapY = mapY = (cameraY / (vSpacing * 2)) - (cameraX / (hSpacing * 2)) - 1;
	
	// How many tiles fits to the view port
	int hTiles, vTiles;
	hTiles = dest->w / (hSpacing * 2);
	vTiles = dest->h / vSpacing;
	
	// Tile position
	int tileX, tileY;
	tileY = -offsetY;
	
	for ( int y = 0; y < vTiles; y++ ){
		if ( y % 2 == 0 ){ // Even row
			tmpMapY++;
			tileX = -offsetX - hSpacing;
		}
		else // Odd row
		{
			tmpMapX++;
			tileX = -offsetX;
		}
		mapX = tmpMapX;
		mapY = tmpMapY;
		for ( int x = 0; x < hTiles; x++ ){
			if ( World->isInsideMap (mapX, mapY) )
			{				
				cell = World->getMapCell (mapX, mapY);
                
                // Render tiles
				const std::vector<unsigned char> &tiles = cell->getTileList();
				for ( unsigned int i = 0; i < tiles.size(); i++ )
					mtileRenderer->renderTile(tiles[i], tileX, tileY, dest);
			}
			
			tileX += hSpacing * 2;
			mapX++;
			mapY--;
		}
		tileY += vSpacing;
	}
}

void mapRenderer::setTileRenderer(tileRenderer *renderer){
	
    mtileRenderer = renderer;
}   
