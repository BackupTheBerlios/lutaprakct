#ifndef TERRAINSPLATTING_H_
#define TERRAINSPLATTING_H_

#include "../material.h"
#include "../../shaders/cgshaders/cgTerrainSplat.h"

class TerrainSplattingMaterial : public Material{
	
	public:
	
		TerrainSplattingMaterial(){};
		TerrainSplattingMaterial(std::string filename){ initialize(filename); };
		virtual ~TerrainSplattingMaterial(){};
		
		void initialize(std::string& filename);
		void bind();
		void unbind();
	
	private:
	
		CgTerrainSplat* splatcg;
};

#endif /*TERRAINSPLATTING_H_*/
