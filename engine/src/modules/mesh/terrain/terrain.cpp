
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
	rootNode = NULL;
}


Terrain::~Terrain(){
	shutDown();
}


bool Terrain::loadMap(char *filename, int detailRepeats){
	
	FILE *fp;

	if(!filename) 
		return false;

	if(heightMap.mapData != NULL) 
		shutDown();

	fp = fopen(filename, "rb");
	if(!fp) 
		return false;

   // Read in the size and the scale values.
	fread(&heightMap.size, 1, sizeof(heightMap.size), fp);
	fread(&heightScale, 1, sizeof(heightScale), fp);

   // Initialize the map data variable.
	heightMap.mapData = new unsigned char[heightMap.size * heightMap.size];
	if(heightMap.mapData == NULL) 
		return false;

   // Read in the entire file into the array.
	fread(heightMap.mapData, 1, heightMap.size * heightMap.size, fp);
	numRepeats = detailRepeats;

	createTerrainMesh();

	fclose(fp);
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
	int size = ((heightMap.size - 1) * (heightMap.size - 1) * 6) * 3;
	int tSize = ((heightMap.size - 1) *(heightMap.size - 1) * 6) * 2;

	vertex = new float[size];
	texCoords = new float[tSize];
	texCoords2 = new float[tSize];

   // Loop through and generate a grid.  Use the height map
   // when setting the Y to create the terrain mesh.  Create 2 triangles
   // each iteration.
	for(int z = 0; z < heightMap.size - 1; z++){
		for(int x = 0; x < heightMap.size - 1; x++){
			      // Calculate texture coords for these tris.
			float left = (float)x / heightMap.size;
			float right = ((float)x + 1) / heightMap.size;
			float bottom = (float)z / heightMap.size;
			float top = (float)(z + 1) / heightMap.size;

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

	if(rootNode) { 
		rootNode->shutdown(); 
		delete rootNode; 
	}

	rootNode = new Octree();
	rootNode->initialize(vertex, totalVerts, texCoords, texCoords2, 5, 1000);

   // dados ja estao na octree
	delete[] vertex; 
	vertex = NULL;
	delete[] texCoords; 
	texCoords = NULL;
	delete[] texCoords2; 
	texCoords2 = NULL;
}


bool Terrain::saveMap(char *filename){
	
	FILE *fp;

   // Error Checking...
	if(heightMap.mapData == 0) return false;
	if(filename == 0) return false;

	// Open the file to write it out as an text file.
	fp = fopen(filename, "wb");
	
   // Error checking.
	if(fp == 0) return false;

   // Write out the size and scale values.
	fwrite(&heightMap.size, 1, sizeof(heightMap.size), fp);
	fwrite(&heightScale, 1, sizeof(heightScale), fp);

	// Write out all of the data in one big write.
	fwrite(heightMap.mapData, 1, heightMap.size * heightMap.size, fp);
	
	// Close the file.
	fclose(fp);
	return true;
}


void Terrain::setHeightScale(float val){
	heightScale = val;
}


void Terrain::setHeight(unsigned char val, int x, int z){
	heightMap.mapData[x + heightMap.size * z] = val;
}


unsigned char Terrain::getHeight(int x, int z){
   // Return the unscaled height value of the specified point.
   return heightMap.mapData[x + heightMap.size * z];
}


float Terrain::getScaledHeight(int x, int z){
   // Return the scaled height value of the specified point.
   return (heightMap.mapData[x + heightMap.size * z] * heightScale);
}


float Terrain::regionPercent(int tileType, unsigned char height){
	
	float distance1 = 0, distance2 = 0;

   // First we test each tile and see if the test height is greater than its optimal height.
   // We only test those that are the type we sent it.
	if(tiles.textureTiles[LOWEST_TILE]){
		if(tileType == LOWEST_TILE && height < tiles.regions[LOWEST_TILE].optimalHeight)
			return 1.0f;
	}else if(tiles.textureTiles[LOW_TILE]){
		if(tileType == LOW_TILE && height < tiles.regions[LOW_TILE].optimalHeight)
			return 1.0f;
	}else if(tiles.textureTiles[HIGH_TILE]){
		if(tileType == HIGH_TILE && height < tiles.regions[HIGH_TILE].optimalHeight)
			return 1.0f;
	}else if(tiles.textureTiles[HIGHEST_TILE]){
		if(tileType == HIGHEST_TILE && height < tiles.regions[HIGHEST_TILE].optimalHeight)
			return 1.0f;
	}

	// If the height we are testing is below or above the choose tile type then we return 0.
	if(height < tiles.regions[tileType].lowHeight)
		return 0.0f;
	else if(height > tiles.regions[tileType].highHeight)
		return 0.0f;

	// If the height is below the optimal height
	if(height < tiles.regions[tileType].optimalHeight){
		   // Get the distance between the tiles lowest height and the test height.
		distance1 = (float)(height - tiles.regions[tileType].lowHeight);

         // Get the distance between the optimal height and the lowest height.
		distance2 = (float)(tiles.regions[tileType].optimalHeight -
		               tiles.regions[tileType].lowHeight);

         // return the percent.
		return (distance1 / distance2);
	}else if(height == tiles.regions[tileType].optimalHeight){
         // Else if the height equals the optimal height we send in full color.
		return 1.0f;
	}else if(height > tiles.regions[tileType].optimalHeight){
		   // Else if the height is greater than the optimal height.
         // Get the distance between the max height from the optimal height.
		distance1 = (float)(tiles.regions[tileType].highHeight -
                         tiles.regions[tileType].optimalHeight);

         // Return the distance - the test height -
         // optimal height / by the distance to get %.
		return((distance1 - (height - tiles.regions[tileType].optimalHeight)) / distance1);
	}

   // Return 0 if we get here.
	return 0.0f;
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


unsigned char Terrain::interpolateHeight(int x, int z, float textureMapRatio){

	unsigned char low = 0, high = 0;
	float interpolatedX = 0.0f, interpolatedZ = 0.0f;
	float interpolation = 0.0f;
	float scaledX = x * textureMapRatio;
	float scaledZ = z * textureMapRatio;

	// Set low as the height of this point.
	low = getHeight((int)scaledX, (int)scaledZ);

	// Set the high value.  If scaled x + 1 is greater than the entire size of the map then
   // we send the low to return as default.  Else we grab the high x.
   // This way we don't go out  of bounds in the array.
	if((scaledX + 1) > heightMap.size)
		return low;
	else
		high = getHeight((int)scaledX + 1, (int)scaledZ);

	// Set the interpolation to be the remainder of scaled x - itself.
	// This will give us a value between  0 and 0.99.  Then we interpolate
	// the high and low.
	interpolation = (scaledX - (int)scaledX);
	interpolatedX = ((high - low) * interpolation) + low;

	// Next we do the same thing for the z that we did for the x.
	if((scaledZ + 1 ) > heightMap.size)
		return low;
	else
		high = getHeight((int)scaledX, (int)scaledZ + 1);

	// Calculate the interpolation for z.
	interpolation = (scaledZ - (int)scaledZ);
	interpolatedZ = ((high - low) * interpolation) + low;

	// Average out the interpolation for the x and z.
	return ((unsigned char)((interpolatedX + interpolatedZ) / 2));
}


unsigned char *Terrain::generateTextureMap(unsigned int imageSize){
	
	
	unsigned char red = 0, green = 0, blue = 0;

	float tu, tv;
	int lastHeight = -1;

	float totalRed = 0, totalGreen = 0, totalBlue = 0;
	
   //quantidade de blend para cada texture tile
	float blendList[MAX_TILES] = {0};
	float textureMapRatio = (float)heightMap.size / (float)imageSize;

	tiles.numTiles = 0;
   
   //ve quantas imagens tem.
	for(int i = 0; i < MAX_TILES; i++){
		if(tiles.textureTiles[i]) tiles.numTiles++;
	}

	if(tiles.numTiles == 0) 
		return NULL;

	for(int i = 0; i < MAX_TILES; i++){
		if(tiles.textureTiles[i]){
			tiles.regions[i].lowHeight = lastHeight + 1;
			lastHeight += 255 / tiles.numTiles;
			tiles.regions[i].optimalHeight = lastHeight;
			tiles.regions[i].highHeight = (lastHeight - tiles.regions[i].lowHeight) + lastHeight;
		}
	}

	unsigned char *image = new unsigned char[imageSize * imageSize * 3];
	
	for(unsigned int z = 0; z < imageSize; z++){
		for(unsigned int x = 0; x < imageSize; x++){
			
			totalRed = 0.0f;
			totalGreen = 0.0f;
			totalBlue = 0.0f;

			// Loop through all tiles and generate each final pixel color.
			for(int i = 0; i < tiles.numTiles; i++){
				// Calculate the texture coords.  This is used to
				// get a pixel from  each tile.
				getTexCoords(tiles.textureTiles[i]->getWidth(),
					tiles.textureTiles[i]->getHeight(), x, z,
					tu, tv);

				// Get the color of the pixel for the set of texture coords.
				int index = (((unsigned int)tv * imageSize) + (unsigned int)tu) * 3;
				red = tiles.textureTiles[i]->img->imagedata[index + 0];
				green = tiles.textureTiles[i]->img->imagedata[index + 1];
				blue = tiles.textureTiles[i]->img->imagedata[index + 2];
         
				// Calculate the amount to blend this pixel with the rest.
				blendList[i] = regionPercent(i, interpolateHeight(x, z, textureMapRatio));

					      // Store the pixel from this tile to the total.
				totalRed += red * blendList[i];
				totalGreen += green * blendList[i];
				totalBlue += blue * blendList[i];
			}

			      // Set a pixel in our final texture image.
			image[((z * imageSize) + x) * 3] = (unsigned char)totalRed;
			image[((z * imageSize) + x) * 3 + 1] = (unsigned char)totalGreen;
			image[((z * imageSize) + x) * 3 + 2] = (unsigned char)totalBlue;
		}
	}

	return image;
}


void Terrain::shutDown(){
   // Release all resources used by the terrain.
	heightScale = 0.0f;
   //tiles.textureTiles[0].FreeImage();
   //tiles.textureTiles[1].FreeImage();
   //tiles.textureTiles[2].FreeImage();
   //tiles.textureTiles[3].FreeImage();
   
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

	if(heightMap.mapData){
		delete[] heightMap.mapData;
		heightMap.mapData = NULL;
		heightMap.size = 0;
	}

	if(rootNode){
		rootNode->shutdown();
		delete rootNode;
		rootNode = NULL;
	}
}
