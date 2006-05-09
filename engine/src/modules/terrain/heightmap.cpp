
#include "heightmap.h"

heightmap::heightmap(std::string filename, int sizex, int sizey){
	initialize(filename, sizex, sizey);
}

bool heightmap::initialize(std::string filename, int sizex, int sizey){

	terrainVerts 	 = new vec3 [sizex * sizey];
	
	for(int i=0, k=0; i<sizex; i++){
		for(int j=0; j<sizey; j++, k++){

			int x, y;

	/*		x = (i * height_map.header.image_info.width) / sizex;
			y = (j * height_map.header.image_info.height) / sizey;

			terrainVerts[(i*sizey)+j].x = (float) i * 10.0f;
			terrainVerts[(i*sizey)+j].y = (float)height_map.image_data[(y*height_map.header.image_info.width*3) + (x * 3)+0] / 8.0f;
			terrainVerts[(i*sizey)+j].z = (float) -j * 10.0f;

			terrainVerts[(i*sizey)+j].y -= 40.0f;
*/
			
		}
	}
	
	
}