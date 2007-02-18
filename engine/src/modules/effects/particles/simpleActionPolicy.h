#ifndef SIMPLEACTIONPOLICY_H_
#define SIMPLEACTIONPOLICY_H_

#include "actionPolicy.h"

class SimpleActionPolicy{

	public:
	
		SimpleActionPolicy(ActionPolicy* color,  ActionPolicy* size,
								ActionPolicy* velocity, ActionPolicy* life,
								ActionPolicy* position, ActionPolicy* force ){
			colorPolicy = color;
			sizePolicy = size;
			velocityPolicy = velocity;
			lifePolicy = life;
			positionPolicy = position;
			forcePolicy = force;
		};
		~SimpleActionPolicy(){};
		
		ActionPolicy* colorPolicy;
		ActionPolicy* sizePolicy;
		ActionPolicy* velocityPolicy;
		ActionPolicy* lifePolicy;
		ActionPolicy* positionPolicy;
		ActionPolicy* forcePolicy;
		
		void initializeAction(Particle& particle){
			colorPolicy->initializeAction(particle);
			sizePolicy->initializeAction(particle);
			velocityPolicy->initializeAction(particle);
			lifePolicy->initializeAction(particle);
			positionPolicy->initializeAction(particle);
			forcePolicy->initializeAction(particle);
		}
		
		void operator()(Particle& particle, float time){
			colorPolicy->action(particle, time);
			sizePolicy->action(particle, time);
			velocityPolicy->action(particle, time);
			lifePolicy->action(particle, time);
			positionPolicy->action(particle, time);
			forcePolicy->action(particle, time);
		}
	
};

#endif /*SIMPLEACTIONPOLICY_H_*/
