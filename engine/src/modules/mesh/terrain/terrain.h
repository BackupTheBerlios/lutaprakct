#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "../../../util/structures/octree.h"
#include "../../material/textures/texturemanager.h"

#include "heightmaps/hillsheightmap.h"

#define MAX_TILES 5


class HeightMap{
	
	public:
	
		HeightMap() { data = 0; size = 0; }
		
		~HeightMap(){
			size = 0;
			if(data) delete []data;
			data = 0;
		}

		int getSizeX(){return size; };
		unsigned char *data;
		int size;
};


enum TILE_TYPES
{
	LOWEST_TILE = 0,        // Dirt and anything under grass.
	LOW_TILE,               // Grass and stuff of that nature.
	HIGH_TILE,              // Moutain sides.
	HIGHEST_TILE            // Top of mountains (snow, etc).
};


struct TextureRegions
{
	int lowHeight;          // Lowest height.
	int optimalHeight;      // Ideal height.
	int highHeight;         // Highest possible height.
};


struct TerrainTiles
{
	TextureRegions regions[MAX_TILES];  // Texture regions.
	texture* textureTiles[MAX_TILES];	// Texture tiles.
	int numTiles;                       // Total number of tiles.
};


class Terrain{
	
	public:
		Terrain();
		~Terrain();

		bool loadMap(char *filename, int detailRepeats);
		bool saveMap(char *filename);
		void createTerrainMesh();

		void setHeightScale(float val);
		void setHeight(unsigned char val, int x, int z);
		unsigned char getHeight(int x, int z);
		float getScaledHeight(int x, int z);

		float regionPercent(int tileType, unsigned char height);
		void getTexCoords(unsigned int texWidth, unsigned int texHeight, unsigned int x,
                        unsigned int z, float &tu, float &tv);
		unsigned char interpolateHeight(int x, int z, float textureMapRatio);
		unsigned char *generateTextureMap(unsigned int imageSize);

		inline bool loadTile(TILE_TYPES tileType, char *filename){
			std::cout << "lendo tile " << filename << std::endl;
            return (tiles.textureTiles[tileType] = TEXTUREMANAGER::getInstance().load(filename, texture::TEXTURE_2D, texture::RGB, texture::RGB8, 0));
		}

		void shutDown();

      // Stores height map and scale value.
		//HeightMap heightMap;
		HillsHeightmap* heightMap;
		float heightScale;
		

      // A list of images used to generate terrain texture.
		TerrainTiles tiles;

      // Vertex list and vertex colors.
		float *vertex;
		float *color;
		float *texCoords;
		float *texCoords2;

		int totalVerts;
		int totalTriangles;
		int numRepeats;

      // Octree to store the entire terrain.
		Octree *rootNode;
};

#endif /*TERRAIN_H_*/
