
#include "../../../../libs/tinyxml/tinyxml.h"
#include "../../../util/misc/xmlconstants.h"
#include "basicTextureMaterial.h"

void BasicTextureMaterial::initialize(std::string& filename){

	TiXmlDocument materialdoc(filename.c_str());
	if (!materialdoc.LoadFile()){
		std::cout << "(BasicTextureMaterial)ERRO: Arquivo de material" <<  filename << " nao encontrado." << std::endl;
		materialdoc.Clear();
		return;
	}
	
	TiXmlElement* meterialcfg = materialdoc.FirstChildElement("material");
	if (!meterialcfg){
		std::cout << "(BasicTextureMaterial)ERRO: Sem tag material." << std::endl;
		materialdoc.Clear();
		return;
	}

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

void BasicTextureMaterial::bind(){
	
	std::list<Texture *>::iterator iter;
	iter = baseTextures.begin();
	
	if (iter != baseTextures.end())
		(*iter)->bind();
	
}

void BasicTextureMaterial::unbind(){
	
	std::list<Texture *>::iterator iter;
	iter = baseTextures.begin();
	
	(*iter)->unbind();	
	
}
