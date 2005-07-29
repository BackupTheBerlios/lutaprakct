
#ifndef _DRAW_FUNCTIONS_H_
#define _DRAW_FUNCTIONS_H_

#include <SDL/SDL.h>

/** Arquivo que contem  funÃ§oes basicas de desenhos
    utilizando diretamente os pixels.
*/

//retorna o pixel em uma posiÃ§ao
Uint32 getpixel(SDL_Surface *surface, int x, int y);
//seta um pixel na teala (passando o pixel)
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
//seta um pixel na tela (passando cada cor RGB)
void putpixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);

//desenha uma linha *bugado :O
void drawline(int x1, int y1, int x2, int y2, SDL_Surface *screen, int r, int g, int b);

//por enquanto so esta sendo usado as funÃ§oes abaixo
void drawVerticalLine(SDL_Surface *surface, int x0, int y0, int y1, Uint8 R, Uint8 G, Uint8 B);
void drawHorizontalLine(SDL_Surface *surface, int y0, int x0, int x1, Uint8 R, Uint8 G, Uint8 B);

void drawgrid(SDL_Surface *surface, int width, int height, int size, Uint8 R, Uint8 G, Uint8 B);

#endif
