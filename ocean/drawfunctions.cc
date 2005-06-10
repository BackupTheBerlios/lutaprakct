
#include "drawfunctions.h"
#include <cmath>
#include <cstdlib>
/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}




/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void putpixel(SDL_Surface *screen, int x, int y,
                                    Uint8 R, Uint8 G, Uint8 B)
{
  Uint32 color = SDL_MapRGB(screen->format, R, G, B);
  switch (screen->format->BytesPerPixel)
  {
    case 1: // Assuming 8-bpp
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
        *bufp = color;
      }
      break;
    case 2: // Probably 15-bpp or 16-bpp
      {
        Uint16 *bufp;
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
        *bufp = color;
      }
      break;
    case 3: // Slow 24-bpp mode, usually not used
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
        {
          bufp[0] = color;
          bufp[1] = color >> 8;
          bufp[2] = color >> 16;
        } else {
          bufp[2] = color;
          bufp[1] = color >> 8;
          bufp[0] = color >> 16;
        }
      }
      break;
    case 4: // Probably 32-bpp
      {
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        *bufp = color;
      }
      break;
  }
}


 /** funÃ§ao de desenhar linha
  * atualmente bugado  
  */

void drawline(int x1, int y1, int x2, int y2, SDL_Surface *screen, int r, int g, int b){
	double m = (double) (y1-y2)/(x1-x2);
    int y = 0;
	for (int i = x1; i<x2; i++){
	    y = abs((int) y1 + m*(i-x1));
		putpixel(screen, i,y,r,g,b);
	}

	int x = 0;
	for (int i = y1; i<y2; i++){
	    x = abs((int) (i-y2)/m + x2);
  putpixel(screen, x,i, r, g, b);
 }
}

 /** desenha a linha de y0 ate y1 no eixo x0. perceba
  * que nao tem tratamento pra caso y1 > y0, a linha 
  * nao sera renderizada.
  */

void drawVerticalLine(SDL_Surface *surface, int x0, int y0, int y1, Uint8 R, Uint8 G, Uint8 B){
 for (int i = y0; i<=y1; i++)
  putpixel(surface, x0, i, R, G, B);
 
}

/** desenha a linha de x0 ate x1 no eixo y0. perceba
  * que nao tem tratamento pra caso x1 > x0, a linha 
  * nao sera renderizada.
  */

void drawHorizontalLine(SDL_Surface *surface, int y0, int x0, int x1, Uint8 R, Uint8 G, Uint8 B){
 for (int i = x0; i<=x1; i++)
  putpixel(surface, i, y0, R, G, B);
 
}

void drawgrid(SDL_Surface *surface, int width, int height, int size, Uint8 R, Uint8 G, Uint8 B){
 for (int x = 0; x <= width; x+=size)
   drawVerticalLine(surface, x, 0, height, R, G, B);
 
 for (int y = 0; y <= height; y+=size)
  drawHorizontalLine(surface, y, 0, width, R, G, B);
}
