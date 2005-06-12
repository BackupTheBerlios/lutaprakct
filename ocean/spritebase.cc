#include "spritebase.h"
#include <string.h>
#include "libs/tinyxml/tinyxml.h"
#include <iostream>

int spriteBase::initialize(char *filename){
	
	int pause=0, r=0, g=0, b=0;
	numframes = 0;
	
	TiXmlDocument *spriteinfo = new TiXmlDocument(filename);
	if (!spriteinfo->LoadFile()){
		std::cout << "file not found: " << filename << std::endl;
		return false;
	}

	TiXmlElement *FrameElem = spriteinfo->FirstChildElement("frame");
	
	while (FrameElem){
    	FrameElem = FrameElem->NextSiblingElement("frame");
		numframes++;
	}
	
	anim = new spriteFrame[numframes];
	FrameElem = spriteinfo->FirstChildElement("frame");
	int i = 0;
	
	while(FrameElem){
		SDL_Surface *aux;
		if((aux = SDL_LoadBMP(FrameElem->Attribute("filename"))) == NULL) return -1;
		r = (int)atoi(FrameElem->Attribute("r"));
		g = (int)atoi(FrameElem->Attribute("g"));
		b = (int)atoi(FrameElem->Attribute("b"));
		if(r >= 0) SDL_SetColorKey(aux, SDL_SRCCOLORKEY, SDL_MapRGB(aux->format, r, g, b));
		anim[i].image = SDL_DisplayFormat(aux);
		SDL_FreeSurface(aux);
		pause = (int)atoi(FrameElem->Attribute("time"));
		w = anim[i].image->w; 
		h = anim[i].image->h;
	}
	
	return 0;
}
