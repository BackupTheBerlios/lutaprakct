#ifndef _ABSTRACTFACTORY_H_
#define _ABSTRACTFACTORY_H_

#include "../interfaces/product.h"
#include <string>

/** interface para abstract factory da engine. todas as factories herdam dela.
 * retorna sempre um product, mas cada subclasse especifica uma interface apropriada
 * pro retorno.
 */

class abstractFactory{
	
public:

    abstractFactory(){};
    virtual ~abstractFactory(){};
	virtual product *create(std::string args) = 0;
	
};

#endif //_ABSTRACTFACTORY_H_
