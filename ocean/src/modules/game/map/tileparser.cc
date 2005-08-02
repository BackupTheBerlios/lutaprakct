
#include "tileparser.h"
#include "../../../libs/tinyxml/tinyxml.h"
#include <iostream>

tilesetParser::tilesetParser(){
}


tilesetParser::~tilesetParser(){
}

void tilesetParser::parse(std::string filename){
	
	TiXmlDocument *tilesetinfo = new TiXmlDocument(filename.c_str());
	if (!tilesetinfo->LoadFile()){
		std::cout << "ERROR: file not found: " << filename << std::endl;
		return;
	}
	 TiXmlElement *imageelem = tilesetinfo->FirstChildElement("image");
	 if (!imageelem)
	 	std::cerr << "o XML nao contem o tag image" << std::endl;
	 tileImage image;
	 imageFilename = imageelem->Attribute("filename");
	 std::cout << "tileset file: "  << imageFilename << std::endl;
	 image.filename = imageFilename;
	 Tileset.push_back(image);

	 TiXmlElement *tileelem = imageelem->FirstChildElement("tile");
	 
	 while (tileelem){
		TiXmlElement *rectelem = tileelem->FirstChildElement("rect");
		TiXmlElement *offelem = tileelem->FirstChildElement("offset");
		
		tileInfo tile;
		tile.name = tileelem->Attribute("name");
		std::cout << "tile name " << tile.name << std::endl;
		
		tile.offsetH = atoi(offelem->Attribute("horizontal"));
		tile.offsetV = atoi(offelem->Attribute("vertical"));
		tile.rectH = atoi(rectelem->Attribute("height"));
		tile.rectW = atoi(rectelem->Attribute("width"));
		tile.rectX = atoi(rectelem->Attribute("x"));
		tile.rectY = atoi(rectelem->Attribute("y"));
	    Tileset.back().tiles.push_back(tile);
	    
 		tileelem = tileelem->NextSiblingElement("tile");
	 }
};