#ifndef ENTITY_H_
#define ENTITY_H_

#include "../util/math/Pivot.h"
#include <string>

enum{
	STATIC = 1,
	SKINNED = 2,
	KEYFRAMED = 3
};

class Entity{
	
	public:
		
		Entity(){};
		virtual ~Entity(){};
		
		virtual bool initialize(std::string, int type) = 0;
		
		void update(float elapsedTime);
		
		virtual void draw() = 0;
		 
		void beginDraw();
		void endDraw();
		
	protected:
	
		Pivotf pivot;
		float time;
		
		int type;
	
};

#endif /*ENTITY_H_*/
