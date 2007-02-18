#ifndef PARTICLEPOLICY_H_
#define PARTICLEPOLICY_H_

#include "particle.h"

class InitializePolicy{
	
	public:
		InitializePolicy(){};
		virtual ~InitializePolicy(){}
		
		virtual void initialize(Particle& particle) = 0;
};

#endif /*PARTICLEPOLICY_H_*/
