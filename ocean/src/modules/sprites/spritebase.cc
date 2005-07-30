#include "spritebase.h"
#include <string.h>
#include "../../libs/tinyxml/tinyxml.h"
#include <iostream>

int spriteBase::initialize(const char *filename){
	
	int r=0, g=0, b=0;
	numframes = 0;
	
	TiXmlDocument *spriteinfo = new TiXmlDocument(filename);
	if (!spriteinfo->LoadFile()){
		std::cout << "ERROR: file not found: " << filename << std::endl;
		return false;
	}

    TiXmlElement *spriteelem = spriteinfo->FirstChildElement("sprite");
	TiXmlElement *FrameElem = spriteelem->FirstChildElement("frame");
	
	while (FrameElem){
    	FrameElem = FrameElem->NextSiblingElement("frame");
		numframes++;
	}
	std::cout << "numero de frames " << numframes << std::endl;
	anim = new spriteFrame[numframes];
	FrameElem = spriteelem->FirstChildElement("frame");
	int i = 0;
	
	while(FrameElem){
		SDL_Surface *aux =  NULL;
		if((aux = SDL_LoadBMP(FrameElem->Attribute("filename"))) == NULL){
			std::cout << "ERRO: nao foi possivel ler o sprite!" << std::endl;
			 return -1;
		}
		r = (int)atoi(FrameElem->Attribute("r"));
		g = (int)atoi(FrameElem->Attribute("g"));
		b = (int)atoi(FrameElem->Attribute("b"));
		if(r >= 0) SDL_SetColorKey(aux, SDL_SRCCOLORKEY, SDL_MapRGB(aux->format, r, g, b));
		anim[i].image = SDL_DisplayFormat(aux);
		SDL_FreeSurface(aux);
		anim[i].pause = (int)atoi(FrameElem->Attribute("time"));
		w = anim[i].image->w; 
		h = anim[i].image->h;
		FrameElem = FrameElem->NextSiblingElement("frame");
		std::cout << "carregando frame numero: " << i << std::endl;
		i++;
	}
	built = 1;
	std::cout << "Base sprite carregado: "  << filename << std::endl;
	return 0;
}
