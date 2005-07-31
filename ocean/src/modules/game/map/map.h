#ifndef _MAP_H_
#define _MAP_H_

#include "mapCell.h"

class world{
	
public:

	world();
	~world();
	
	bool initialize(int width, int height);
	void shutdown();
	
	mapCell *getMapCell (int x, int y);
    
	int getWidth (void) { return width; }
	int getHeight (void) { return height; }
        
	bool isInsideMap (int x, int y)
	{
		if ( x >= 0 && y >= 0 && x < width && y < height )
			return true;
		return false;
	}
	
private:

	mapCell *mapCells;
	int width;
	int height;
	
};

#endif //_MAP_H_
