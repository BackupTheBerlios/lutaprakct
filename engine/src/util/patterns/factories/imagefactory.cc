
#include "imagefactory.h"

#include "../../image/image.h"
#include "../../image/tgaimage.h"
#include <cstring>

product* imageFactory::create(std::string filename){
	
	char *aux = strchr (filename.c_str(), '.');
	aux++;
	
	image *ret;
	if ((strcmp (aux, "TGA") == 0) || (strcmp (aux, "tga") == 0)){
        ret = new tgaimage(filename.c_str());
        return ret;
	}
	
}
