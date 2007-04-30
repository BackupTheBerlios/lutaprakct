
#include "materialFactory.h"
#include "materials/basicTextureMaterial.h"
#include "materials/terrainSplattingMaterial.h"
#include "../../../libs/tinyxml/tinyxml.h"
#include <iostream>

Material* MaterialFactory::loadMaterial(std::string& filename){
		
		TiXmlDocument materialdoc(filename.c_str());
		if (!materialdoc.LoadFile()){
			std::cout << "(MaterialFactory) ERRO: Arquivo de material " << filename << " nao encontrado." << std::endl;
			materialdoc.Clear();
			return NULL;
		}
		
		
		TiXmlElement* materialcfg = materialdoc.FirstChildElement("material");
		if (!materialcfg){
			std::cout<< "(MaterialFactory) ERRO: Arquivo de material sem tag material" << std::endl;
			materialdoc.Clear();
			return NULL;			
		}
		
		TiXmlElement* classcfg = materialcfg->FirstChildElement("materialclass");
		if (!classcfg){
			std::cout<< "(MaterialFactory) ERRO: Arquivo de material sem tag materialclass" << std::endl;
			materialdoc.Clear();
			return NULL;
		}
		std::string classname = classcfg->Attribute("name");
		
		Material* ret = NULL;
		
		materialdoc.Clear();
		if (classname == "terrainsplatting")
			ret = new TerrainSplattingMaterial(filename);
		else if (classname == "basictexture")
			ret = new BasicTextureMaterial(filename);
		
		
		return ret;
}; 
