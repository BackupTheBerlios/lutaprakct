#include "font.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>

void font::draw (SDL_Surface *screen, SDL_Surface *img, int x, int y, int h, int w, int x2, int y2)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_Rect src;
	src.x = x2;
	src.y = y2;
	src.h = h;
	src.w = w;
	SDL_BlitSurface(img, &src, screen, &dest);
}

void font::initialize(char *fontdir, float r, float g, float b, float a)
{
	SDLFont *tempFont;
	FILE *fp;
	char tempString[100];
	unsigned char tmp;
	int width;
	SDL_Surface *tempSurface;
	
	sprintf(tempString, "%s/%s", fontdir, "font.ini");
	fp = fopen (tempString, "rb");
	if (fp == NULL)
	{
		return;
	}
	  fscanf(fp, "%d", &width);
  fclose(fp);
	tempFont = new SDLFont;
	tempFont->data = new unsigned char [width*width*4];
	tempFont->width = width;
	tempFont->charWidth = width/16;
	
	sprintf(tempString, "%s/%s", fontdir, "font.raw");
	fp = fopen (tempString, "rb");
	if (fp != NULL)
	{
		for (int i=0; i < width*width; i++)
		{
			tmp = fgetc(fp);
			tempFont->data[i*4] = (unsigned char) 255*(unsigned char) r;
			tempFont->data[i*4 + 1] = (unsigned char) 255*(unsigned char) g;
			tempFont->data[i*4 + 2] = (unsigned char) 255*(unsigned char) b;
			tempFont->data[i*4 + 3] = (unsigned char) (((float) tmp) *a);
		}
	} else {
		return;
	}
	fclose (fp);
	
	Uint32 rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
	#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
	#endif
	tempSurface = SDL_CreateRGBSurfaceFrom(tempFont->data, width, width, 32, width*4, rmask, gmask, bmask, amask);
	tempFont->font = SDL_DisplayFormatAlpha(tempSurface);
	SDL_FreeSurface(tempSurface);
	
	tempFont->widths = new int[256];
	sprintf(tempString, "%s/%s", fontdir, "font.dat");
	fp = fopen(tempString, "rb");
	if (fp != NULL)
	{
		for (int i = 0; i < 256; i++)
		{
			tmp = fgetc(fp);
			tempFont->widths[i] = tmp;
		} 
	}
	fclose(fp);
	font1 = tempFont;
}

void font::drawString(SDL_Surface *screen,  int x, int y, char *str, ...)
{
	char string[1024];
	
	va_list ap;
	va_start(ap, str);
	vsprintf(string, str, ap);
	va_end(ap);
	
	int len = strlen(string);
	int xx = 0;	
	for (int i = 0; i < len; i++)
	{
		draw(screen, font1->font, xx+x, y, font1->widths[string[i]]+6, font1->charWidth,
						(string[i]%16*font1->charWidth)+((font1->charWidth/2) - (font1->widths[string[i]])/2),
						(((int) string[i]/16)*font1->charWidth));
		
		xx+=font1->widths[string[i]];							 
	}
}

int font::getStringWidth(SDLFont *font, char *str, ...)
{
	char string[1024];
	va_list ap;
	va_start(ap, str);
	vsprintf(string, str, ap);
	va_end(ap);
	
	int xx = 0;
	int len=strlen(string);
	for (int i =0; i < len; i++)
	{
		xx+=font->widths[string[i]];
	}
	return xx;
}

void font::free()
{
	delete [] font1->widths;
	delete [] font1->data;
	SDL_FreeSurface(font1->font);
	delete font1;
}
