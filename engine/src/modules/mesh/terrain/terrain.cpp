
#include<stdio.h>

#include "terrain.h"
#include "../../../util/logger/logger.h"


Terrain::Terrain(){
	heightScale = 0.0f;
	vertex = NULL;
	texCoords = NULL;
	texCoords2 = NULL;
	totalVerts = 0;
	totalTriangles = 0;
	numRepeats = 1;
	heightMap = NULL;
	terrainMaterial = NULL;
}


Terrain::~Terrain(){
	shutDown();
}


bool Terrain::loadMap(char *filename, int detailRepeats){

	if(!filename) 
		return false;

	heightMap = new HillsHeightmap();
	//heightMap->generate(256, 256, 0.0, 40.0, 1200, 1);
	std::string file(filename);
	heightMap->load(file);
	heightScale = 0.1;

	numRepeats = detailRepeats;
	createTerrainMesh();

	return true;
}


void Terrain::createTerrainMesh(){

	int i = 0, t = 0, t2 = 0;
	totalVerts = 0;
	totalTriangles = 0;

	if(vertex) 
		delete[] vertex;
	if(texCoords) 
		delete[] texCoords;
	if(texCoords2) 
		delete[] texCoords2;

   //Sizes we need for the points/color and tex coords.
	int size = ((heightMap->getSizeX() - 1) * (heightMap->getSizeX() - 1) * 6) * 3;
	int tSize = ((heightMap->getSizeX() - 1) *(heightMap->getSizeX() - 1) * 6) * 2;

	vertex = new float[size];
	texCoords = new float[tSize];
	texCoords2 = new float[tSize];

   // Loop through and generate a grid.  Use the height map
   // when setting the Y to create the terrain mesh.  Create 2 triangles
   // each iteration.
	for(int z = 0; z < heightMap->getSizeX() - 1; z++){
		for(int x = 0; x < heightMap->getSizeX() - 1; x++){
			      // Calculate texture coords for these tris.
			float left = (float)x / heightMap->getSizeX();
			float right = ((float)x + 1) / heightMap->getSizeX();
			float bottom = (float)z / heightMap->getSizeX();
			float top = (float)(z + 1) / heightMap->getSizeX();

               // V1.

			texCoords[t++] = left * numRepeats;//0.0;//left;
			texCoords[t++] = bottom * numRepeats;//0.0;//bottom;
			texCoords2[t2++] = left;//left * numRepeats;
			texCoords2[t2++] = bottom;//bottom * numRepeats;
			vertex[i++] = (float)x;
			vertex[i++] = getScaledHeight(x, z);
			vertex[i++] = (float)z;
			totalVerts++;
           // LOGGER::getInstance().write("heightmap.log", "V1 texCords: %f textCoords: %f TexCoords2: %f texCoords2: %f X: %d Y: %f z: %d \n", left, bottom, left*numRepeats, bottom*numRepeats, x, getScaledHeight(x, z), z );

               // V2.
			texCoords[t++] = left * numRepeats;//0.0;//left;
			texCoords[t++] = top * numRepeats;//1.0;//top;
			texCoords2[t2++] = left;//left * numRepeats;
			texCoords2[t2++] = top;//top * numRepeats;
			vertex[i++] = (float)x;
			vertex[i++] = getScaledHeight(x, z + 1);
			vertex[i++] = (float)z + 1;
			totalVerts++;
           // LOGGER::getInstance().write("heightmap.log", "V2 texCords: %f textCoords: %f TexCoords2: %f texCoords2: %f X: %d Y: %f z: %d \n", left, top, left*numRepeats, top*numRepeats, x, getScaledHeight(x, z+1), z+1 );

               // V3.
			texCoords[t++] = right * numRepeats;//1.0;//right;
			texCoords[t++] = bottom * numRepeats;//0.0;//bottom;
			texCoords2[t2++] = right;//right * numRepeats;
			texCoords2[t2++] = bottom;//bottom * numRepeats;
			vertex[i++] = (float)x + 1;
			vertex[i++] = getScaledHeight(x + 1, z);
			vertex[i++] = (float)z;
			totalVerts++;
            //LOGGER::getInstance().write("heightmap.log", "V3 texCords: %f textCoords: %f TexCoords2: %f texCoords2: %f X: %d Y: %f z: %d \n", right, bottom, right*numRepeats, bottom*numRepeats, x+1, getScaledHeight(x+1, z), z );

               // V4.
			texCoords[t++] = right * numRepeats;//1.0;//right;
			texCoords[t++] = bottom * numRepeats;//0.0;//bottom;
			texCoords2[t2++] = right;//right * numRepeats;
			texCoords2[t2++] = bottom;//bottom * numRepeats;
			vertex[i++] = (float)x + 1;
			vertex[i++] = getScaledHeight(x + 1, z);
			vertex[i++] = (float)z;
			totalVerts++;
            //LOGGER::getInstance().write("heightmap.log", "V4 texCords: %f textCoords: %f TexCoords2: %f texCoords2: %f X: %d Y: %f z: %d \n", right, bottom, right*numRepeats, bottom*numRepeats, x+1, getScaledHeight(x+1, z), z );

               // V5.
			texCoords[t++] = right * numRepeats;//1.0;//right;
			texCoords[t++] = top * numRepeats;//1.0;//top;
			texCoords2[t2++] = right;//right * numRepeats;
			texCoords2[t2++] = top;//top * numRepeats;
			vertex[i++] = (float)x + 1;
			vertex[i++] = getScaledHeight(x + 1, z + 1);
			vertex[i++] = (float)z + 1;
			totalVerts++;
            //LOGGER::getInstance().write("heightmap.log", "V5 texCords: %f textCoords: %f TexCoords2: %f texCoords2: %f X: %d Y: %f z: %d \n", right, top, right*numRepeats, top*numRepeats, x+1, getScaledHeight(x+1, z+1), z+1 );

               // V6.
			texCoords[t++] = left * numRepeats;//0.0;//left;
			texCoords[t++] = top * numRepeats;//1.0;//top;
			texCoords2[t2++] = left;//left * numRepeats;
			texCoords2[t2++] = top;//top * numRepeats;
			vertex[i++] = (float)x;
			vertex[i++] = getScaledHeight(x, z + 1);
			vertex[i++] = (float)z + 1;
			totalVerts++;
            //LOGGER::getInstance().write("heightmap.log", "V6 texCords: %f textCoords: %f TexCoords2: %f texCoords2: %f X: %d Y: %f z: %d \n", left, top, left*numRepeats, top*numRepeats, x, getScaledHeight(x, z+1), z+1 );

			totalTriangles += 2;
		}
	}

	std::cout << "Total terrain triangles: " << totalTriangles << std::endl;


}


bool Terrain::saveMap(char *filename){
	std::string file(filename);
	heightMap->save(file);
	return true;
}


void Terrain::setHeightScale(float val){
	heightScale = val;
}


void Terrain::setHeight(unsigned char val, int x, int z){
	heightMap->data[x + heightMap->getSizeX() * z] = val;
}


unsigned char Terrain::getHeight(int x, int z){
   return heightMap->data[x + heightMap->getSizeX() * z];
}


float Terrain::getScaledHeight(int x, int z){
   return (heightMap->data[x + heightMap->getSizeX() * z] * heightScale);
}

float Terrain::getScaledInterpolatedHeight(float x, float z){
	
	float projCameraX, projCameraZ;

	projCameraX = x / 1.0;
	projCameraZ = z / 1.0;


	int col0 = int(projCameraX);
	int row0 = int(projCameraZ);
	int col1 = col0 + 1;
	int row1 = row0 + 1;
		
	if (col1 > heightMap->getSizeX())
		col1 = 0;
	if (row1 > heightMap->getSizeY())
		row1 = 0;

	float h00 = heightScale * (float)heightMap->data[col0 + row0*heightMap->getSizeX()];
	float h01 = heightScale * (float)heightMap->data[col1 + row0*heightMap->getSizeX()];
	float h11 = heightScale * (float)heightMap->data[col1 + row1*heightMap->getSizeX()];
	float h10 = heightScale * (float)heightMap->data[col0 + row1*heightMap->getSizeX()];

	//pega a margem de erro, do float x, z pro inteiro
	float tx = projCameraX - float(col0);
	float ty = projCameraZ - float(row0);

	//interpolacao bilinear
	float txty = tx * ty;

	float final_height = h00 * (1.0f - ty - tx + txty)
					+ h01 * (tx - txty)
					+ h11 * txty
					+ h10 * (ty - txty);

	return final_height;
	
}

void Terrain::getTexCoords(unsigned int texWidth, unsigned int texHeight,
                            unsigned int x, unsigned int z, float &tu, float &tv){
   // These two will store the amount of times the texture
   // repeats across the terrain along the x and z.
	int totalWidthRepeats = -1;
	int totalHeightRepeats = -1;

   // Temp number to hold temp values.
	int i = 0;

	// Calculate the amount of times this image would repeat across the x.
	while(totalWidthRepeats == -1){
		i++;

		   // We test if this point (x value) is less than the width times i.
         // If x is 156 and the image width is 256 then it will not repeat.
         // If x is 512 and the image width is 256 then the image will repeat
         // at least 1 time.
		if(x < (texWidth * i)) totalWidthRepeats = i - 1;
	}

	// Reset.
	i = 0;

	// Calculate the amount of times this image would repeat across the z.
	while(totalHeightRepeats == -1){
		i++;

		   // Same as with the x.
		if(z < (texHeight * i)) totalHeightRepeats = i - 1;
	}

	// Calculate the final texture coordinate.
	tu = (float)(x - (texWidth * totalWidthRepeats));
	tv = (float)(z - (texHeight * totalHeightRepeats));
}

void Terrain::shutDown(){
   
	if(vertex){
		delete[] vertex;
		vertex = NULL;
	}
   
	if(color){
		delete[] color;
		color = NULL;
	}

	if(texCoords){
		delete[] texCoords;
		texCoords = NULL;
	}

	if(texCoords2){
		delete[] texCoords2;
		texCoords2 = NULL;
	}

}
