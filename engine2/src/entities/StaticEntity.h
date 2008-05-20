#ifndef STATICENTITY_H_
#define STATICENTITY_H_

#include "Entity.h"

/* meshes que nao mudam seu dados e nao tem animacoes */

class StaticEntity : public Entity{

	public:
		
		StaticEntity(){};
		virtual ~StaticEntity(){};
		
		virtual bool initialize(char* filename);
		
		virtual void draw();	

	
};


#endif /*STATICENTITY_H_*/
