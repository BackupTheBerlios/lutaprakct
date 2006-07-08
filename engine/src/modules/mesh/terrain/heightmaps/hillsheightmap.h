#ifndef HILLSHEIGHTMAP_H_
#define HILLSHEIGHTMAP_H_

#include "heightmap.h"

class HillsHeightmap : public Heightmap{
	
	public:
	
		HillsHeightmap(){tempData = NULL;};
		~HillsHeightmap(){ if (data){ free(data); data = NULL; }
						   if (tempData){ delete tempData; tempData = NULL;}
		};
		
		void generate( unsigned short	 sizex, unsigned short sizey, float hillMin,
						float hillMax, unsigned short numHills, 
						unsigned short	flattening, bool isIsland = false);
						
		void clearTempData();
		
	private:

		float getCell(unsigned int x, unsigned int y);
		void setCell(unsigned int x, unsigned int y, float value);
		
		void addHeight(unsigned int x, unsigned int y, float value);
		void normalize();		
		void addHill();
		void flatten();
		void writeData();
		
		float hillMin, hillMax;
		unsigned short numHills;
		bool isIsland;
		unsigned short flattening;
	
		float* tempData;
	
};

#endif /*HILLSHEIGHTMAP_H_*/
