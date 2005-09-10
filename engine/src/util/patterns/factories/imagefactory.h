#ifndef _IMAGEFACTORY_H_
#define _IMAGEFACTORY_H_


#include "../abstractfactory.h"
#include "../singleton.h"

/*factory das images
 */

class imageFactory : public abstractFactory {
	
public:
	imageFactory(){};
	~imageFactory(){};
    product* create(std::string filename);
	
	
};

typedef singleton<imageFactory> ImageFactory;

#endif //_IMAGEFACTORY_H_
