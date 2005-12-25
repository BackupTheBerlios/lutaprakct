
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <list>
#include <string>


struct layer {
	SDL_Surface *layers;
	int position; 
	std::string name;
};


class background {
public:
	void drawbg();
	void addlayer(std::string layer, int x);
private:
	SDL_Surface *back;
	std::list<layer*> layers;
};

#endif
