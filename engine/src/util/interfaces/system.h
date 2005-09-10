#ifndef _SYSTEM_H_
#define _SYSTEM_H_

/** system é a classe base pra todos os systems que existir na engine.
 * todos os systems devem herdar dela.
 */

#include "product.h"

class systemInterface : public product{
	
public:
   systemInterface(){};
   virtual ~systemInterface(){};
	
};

#endif //_SYSTEM_H_
