
#include "Terrain.h"
#include "../../util/image/tgaimage.h"

Terrain::Terrain(){
}

Terrain::~Terrain(){
}

bool Terrain::loadHeightMap(std::string filename){

	TgaImage* tga = new TgaImage(filename);
	if (!tga)
		return false;
		
	width = tga->getWidth();
	height = tga->getHeight();
	
	heightMapData = new unsigned char[width * height];
	
	int j = 0;
	for (int i = 0; i < width*height; i++){
		(heightMapData[i]) = (tga->imagedata[j]);
		j += 3;
	}
	
	delete tga;
	
	if (!generateGeometry())
		return false;
	
	return true;
	
}

bool Terrain::generateGeometry(){

	int i = 0, t = 0, t2 = 0;
	totalVerts = 0;
	totalTriangles = 0;

	if(vertex) 
		delete[] vertex;
	if(texCoords1) 
		delete[] texCoords1;
	if(texCoords2) 
		delete[] texCoords2;

	int size = ((width - 1) * (width - 1) * 6) * 3;
	int tSize = ((width - 1) *(width - 1) * 6) * 2;

	vertex = new float[size];
	texCoords1 = new float[tSize];
	texCoords2 = new float[tSize];

   // Loop through and generate a grid.  Use the height map
   // when setting the Y to create the terrain mesh.  Create 2 triangles
   // each iteration.
	for(int z = 0; z < width - 1; z++){
		for(int x = 0; x < width - 1; x++){
			      // Calculate texture coords for these tris.
			float left = (float)x / width;
			float right = ((float)x + 1) / width;
			float bottom = (float)z / width;
			float top = (float)(z + 1) / width;

               // V1.
			texCoords[t++] = left * numRepeats;//0.0;//left;
			texCoords[t++] = bottom * numRepeats;//0.0;//bottom;
			texCoords2[t2++] = left;//left * numRepeats;
			texCoords2[t2++] = bottom;//bottom * numRepeats;
			vertex[i++] = (float)x;
			vertex[i++] = getScaledHeight(x, z);
			vertex[i++] = (float)z;
			totalVerts++;

               // V2.
			texCoords[t++] = left * numRepeats;//0.0;//left;
			texCoords[t++] = top * numRepeats;//1.0;//top;
			texCoords2[t2++] = left;//left * numRepeats;
			texCoords2[t2++] = top;//top * numRepeats;
			vertex[i++] = (float)x;
			vertex[i++] = getScaledHeight(x, z + 1);
			vertex[i++] = (float)z + 1;
			totalVerts++;

               // V3.
			texCoords[t++] = right * numRepeats;//1.0;//right;
			texCoords[t++] = bottom * numRepeats;//0.0;//bottom;
			texCoords2[t2++] = right;//right * numRepeats;
			texCoords2[t2++] = bottom;//bottom * numRepeats;
			vertex[i++] = (float)x + 1;
			vertex[i++] = getScaledHeight(x + 1, z);
			vertex[i++] = (float)z;
			totalVerts++;

               // V4.
			texCoords[t++] = right * numRepeats;//1.0;//right;
			texCoords[t++] = bottom * numRepeats;//0.0;//bottom;
			texCoords2[t2++] = right;//right * numRepeats;
			texCoords2[t2++] = bottom;//bottom * numRepeats;
			vertex[i++] = (float)x + 1;
			vertex[i++] = getScaledHeight(x + 1, z);
			vertex[i++] = (float)z;
			totalVerts++;

               // V5.
			texCoords[t++] = right * numRepeats;//1.0;//right;
			texCoords[t++] = top * numRepeats;//1.0;//top;
			texCoords2[t2++] = right;//right * numRepeats;
			texCoords2[t2++] = top;//top * numRepeats;
			vertex[i++] = (float)x + 1;
			vertex[i++] = getScaledHeight(x + 1, z + 1);
			vertex[i++] = (float)z + 1;
			totalVerts++;

               // V6.
			texCoords[t++] = left * numRepeats;//0.0;//left;
			texCoords[t++] = top * numRepeats;//1.0;//top;
			texCoords2[t2++] = left;//left * numRepeats;
			texCoords2[t2++] = top;//top * numRepeats;
			vertex[i++] = (float)x;
			vertex[i++] = getScaledHeight(x, z + 1);
			vertex[i++] = (float)z + 1;
			totalVerts++;

			totalTriangles += 2;
		}
	}

	return true;
}

bool Terrain::saveHeightMap(std::string filename){

	TgaImage* tga = new TgaImage();
	unsigned char* greyToRGBData = new unsigned char[width * height * 3];
	
	int j = 0;
	for (int i = 0; i < width*height; i++){
		greyToRGBData[j++] = heightMapData[i];
		greyToRGBData[j++] = heightMapData[i];
		greyToRGBData[j++] = heightMapData[i];
	}
	tga->write(filename, width, height, 24, greyToRGBData);
	delete []greyToRGBData;
	delete tga;
	
	return true;
}

float Terrain::getScaledHeight(int x, int z){
   return (heightMapData[x + width * z] * heightScale);
}
