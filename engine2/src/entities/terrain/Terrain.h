#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <string>

class Terrain{

	public:
	
		Terrain();
		~Terrain();
		
		bool loadHeightMap(std::string filename);
		bool saveHeightMap(std::string filename);
		
	private:
		
		bool generateGeometry();
		
		float getScaledHeight(int x, int y);
		
		int width, height;
		float heightScale;
		unsigned char* heightMapData;
		
		int totalVerts, totalTriangles;
		float* vertex;
		float* texCoords1;
		float* texCoords2;
};

#endif /*TERRAIN_H_*/
