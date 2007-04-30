#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "../../material/textures/texturemanager.h"
#include "../../material/material.h"
#include "heightmaps/hillsheightmap.h"

#define MAX_TILES 5


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
		float getScaledInterpolatedHeight(float x, float z);

		void getTexCoords(unsigned int texWidth, unsigned int texHeight, unsigned int x,
                        unsigned int z, float &tu, float &tv);

		void shutDown();

		void bindMaterial(){
			if (terrainMaterial)
				terrainMaterial->bind();
		}
		
		void unbindMaterial(){
			if (terrainMaterial)
				terrainMaterial->unbind();
		}

		void setMaterial(Material* m){ 
			terrainMaterial = m;
		}

		HillsHeightmap* heightMap;
		float heightScale;

      // Vertex list and vertex colors.
		float *vertex;
		float *color;
		float *texCoords;
		float *texCoords2;

		int totalVerts;
		int totalTriangles;
		int numRepeats;

	private:
	
		Material* terrainMaterial;

};

#endif /*TERRAIN_H_*/
