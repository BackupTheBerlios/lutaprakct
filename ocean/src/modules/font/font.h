#ifndef _FONT_H_
#define _FONT_H_


#include <SDL/SDL.h>

struct SDLFont
{
	SDL_Surface *font;
	int width;
	int charWidth;
	int *widths;
	unsigned char *data;
};

class font {

public:
	void draw(SDL_Surface *screen, SDL_Surface *img, int x, int y, int w, int h, int x2, int y2);
	void initialize(char *fontdir, float r, float g, float b, float a);
	void drawString(SDL_Surface *screen,  int x, int y, char *str, ...);
	int getStringWidth(SDLFont *font, char *str, ...);
	void free();
	
private:
	SDLFont *font1;
	
};
#endif
