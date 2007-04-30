
#include <cstring>
#include "image.h"
#include "tgaimage.h"

Image* loadImage(std::string& filename){

	char* aux = strchr (filename.c_str(), '.');
	aux++;
	Image *ret;
	if ((strcmp (aux, "TGA") == 0) || (strcmp (aux, "tga") == 0)){
        ret = new TgaImage(filename);
        return ret;
	}
	return NULL;
}
