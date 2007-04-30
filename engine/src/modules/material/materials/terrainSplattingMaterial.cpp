
#include "terrainSplattingMaterial.h"
#include "../../../../libs/tinyxml/tinyxml.h"
#include "../../../util/misc/xmlconstants.h"
#include <iostream>

void TerrainSplattingMaterial::initialize(std::string& filename){

	TiXmlDocument materialdoc(filename.c_str());
	if (!materialdoc.LoadFile()){
		std::cout << "(TerrainSplattingMaterial)ERRO: Arquivo de material" <<  filename << " nao encontrado." << std::endl;
		materialdoc.Clear();
		return;
	}
	
	TiXmlElement* meterialcfg = materialdoc.FirstChildElement("material");
	if (!meterialcfg){
		std::cout << "(TerrainSplattingMaterial)ERRO: Sem tag material." << std::endl;
		materialdoc.Clear();
		return;
	}
	
	TiXmlElement* shadercfg = meterialcfg->FirstChildElement("shader");
	if (shadercfg){
		std::string shaderfilename = shadercfg->Attribute("filename");
		//TODO ler o xml ou nao
		splatcg = new CgTerrainSplat(NULL, 0, "terrainSplatting.cg", PROFILE_ARBFP1, 0);
		splatcg->compile();
		splatcg->unbind();
		
	}
	
	//verifica se tem texutras e carrega
	TiXmlElement* textures = meterialcfg->FirstChildElement("texture");
	while(textures){
		std::string textureName(textures->Attribute("filename"));
		Texture* t = TEXTUREMANAGER::getInstance().load(textureName, 
						getXmlConstant(textures->Attribute("type")), 
						getXmlConstant(textures->Attribute("format")), 
						getXmlConstant(textures->Attribute("internalformat")), 
						getXmlTextureFlags(textures->Attribute("flags")));
		baseTextures.push_back(t);
		textures = textures->NextSiblingElement("texture");	
	}
	materialdoc.Clear();
}

void TerrainSplattingMaterial::bind(){
	
	splatcg->bind();
	
	int i = 0;
	std::list<Texture *>::iterator iter;
	for (iter = baseTextures.begin(); iter != baseTextures.end(); iter++){
		(*iter)->bind(i);
		i++;
	}
	
	
}

void TerrainSplattingMaterial::unbind(){

	splatcg->unbind();
	std::list<Texture *>::iterator iter;
	
	for (iter = baseTextures.begin(); iter != baseTextures.end(); iter++){
		(*iter)->unbind();
	}
	
}
