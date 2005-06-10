#include "spritebase.h"
#include <string.h>

int spriteBase::initialize(char *dir){
	
  char buffer[255];
  char filename[255];
  char name[255];
  int pause=0, r=0, g=0, b=0;
  FILE *fp;

  sprintf(filename, "%s/info", dir);

  if((fp=fopen(filename, "r")) == NULL){
    printf("ERROR opening file %s\n\n", filename);
    return -1;
  }

  fgets(buffer, 255, fp);
  sscanf(buffer, "FILES: %d", &numframes);
  anim = new spriteFrame[numframes];

  built = 1;
  int count = 0;

  while(!feof(fp) && count<numframes)
  {
    fgets(buffer, 255, fp);
    if(buffer[0] != '#' && buffer[0] != '\r' && buffer[0] != '\0' && buffer[0] != '\n' && strlen(buffer) != 0)
    {
      sscanf(buffer, "%s %d %d %d %d", name, &pause, &r, &g, &b);
      sprintf(filename, "%s/%s", dir, name);
      SDL_Surface *temp;
      if((temp = SDL_LoadBMP(filename)) == NULL) return -1;
      if(r >= 0) SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, r, g, b));
      anim[count].image = SDL_DisplayFormat(temp);
      SDL_FreeSurface(temp);

      anim[count].pause = pause;
      if(!w) w = anim[count].image->w; if(!h) h = anim[count].image->w;

      count++;
    }
  }
  fclose(fp);
  return 0;
}
