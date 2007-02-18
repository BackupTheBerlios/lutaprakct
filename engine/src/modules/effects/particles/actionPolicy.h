#ifndef ACTIONPOLICY_H_
#define ACTIONPOLICY_H_

#include "particle.h"

class ActionPolicy{
	
	public:
		ActionPolicy(){};
		virtual ~ActionPolicy(){}
		
		virtual void initializeAction(Particle& particle) = 0;
		virtual void action(Particle& particle, float time) = 0;
};

#endif /*ACTIONPOLICY_H_*/
