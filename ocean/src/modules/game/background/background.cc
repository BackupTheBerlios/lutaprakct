
#include "background.h"
#include <iostream>

void background::drawbg() {
	SDL_Surface *vidio;
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	vidio = SDL_GetVideoSurface();
	std::list<layer*>::iterator iter;
	for (iter = layers.begin(); iter != layers.end(); iter++) {
		SDL_BlitSurface ((*iter)->layers , NULL,vidio, &dest);
	}
}

void background::addlayer(std::string filename, int x) {
	layer *layer1 = new layer;
	layer1->position = x;
	layer1->name = filename;
	layer1->layers =(SDL_Surface *) IMG_Load (filename.c_str());
	layers.push_back(layer1);
}
