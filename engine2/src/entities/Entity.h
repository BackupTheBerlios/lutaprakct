#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>
#include "../util/math/Pivot.h"

enum{
	STATICMESH = 1,
	SKINNEDMESH = 2,
	KEYFRAMEDMESH = 3
};

class Entity{
	
	public:
		
		Entity(){};
		virtual ~Entity(){};
		
		virtual bool initialize(char*) = 0;
		
		void update(float elapsedTime){};
		
		virtual void draw() = 0;
		 
		void beginDraw(){};
		void endDraw(){};
		
	protected:
	
		Pivotf pivot;
		float time;
		
		int type;
		
	
};

#endif /*ENTITY_H_*/
