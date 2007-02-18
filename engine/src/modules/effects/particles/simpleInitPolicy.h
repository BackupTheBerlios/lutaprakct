#ifndef BASEPARTICLEPOLICY_H_
#define BASEPARTICLEPOLICY_H_

#include "initializePolicy.h"

class SimpleInitializePolicy{

	public:
	
		SimpleInitializePolicy(InitializePolicy* color,  InitializePolicy* size,
								InitializePolicy* velocity, InitializePolicy* life,
								InitializePolicy* position, InitializePolicy* force ){
			colorPolicy = color;
			sizePolicy = size;
			velocityPolicy = velocity;
			lifePolicy = life;
			positionPolicy = position;
			forcePolicy = force;
		};
		~SimpleInitializePolicy(){};
		
		InitializePolicy* colorPolicy;
		InitializePolicy* sizePolicy;
		InitializePolicy* velocityPolicy;
		InitializePolicy* lifePolicy;
		InitializePolicy* positionPolicy;
		InitializePolicy* forcePolicy;
		
		void operator()(Particle& particle){
			colorPolicy->initialize(particle);
			sizePolicy->initialize(particle);
			velocityPolicy->initialize(particle);
			lifePolicy->initialize(particle);
			positionPolicy->initialize(particle);
			forcePolicy->initialize(particle);
		}
	
};

#endif /*BASEPARTICLEPOLICY_H_*/
