
#include <cstring>
#include "image.h"
#include "tgaimage.h"

image* loadImage(const char* filename){

	char* aux = strchr (filename, '.');
	aux++;
	image *ret;
	if ((strcmp (aux, "TGA") == 0) || (strcmp (aux, "tga") == 0)){
        ret = new tgaimage(filename);
        return ret;
	}
	return NULL;
}
