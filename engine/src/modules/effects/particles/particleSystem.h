#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_

#include "particle.h"
#include "simpleActionPolicy.h"
#include "simpleInitPolicy.h"

#include <list>

class ParticleSystem{
	
	public:
		
		ParticleSystem(InitializePolicy* colorinit, InitializePolicy* sizeinit, InitializePolicy* velocityinit, InitializePolicy* lifeinit, InitializePolicy* positioninit, InitializePolicy* forceinit, ActionPolicy* coloraction, ActionPolicy* sizeaction, ActionPolicy* velocityaction, ActionPolicy* lifeaction, ActionPolicy* positionaction, ActionPolicy* forceaction );
	
	private:
	
		SimpleInitializePolicy* initPolicy;
		SimpleActionPolicy* actionPolicy; 
		//Cmaterial *material;
		
		std::list<Particle*> particles;
		unsigned int currentNum;
		unsigned int maxNum;
    	float position[3];
    	float currentTime;
    	float lastUpdate;
    	float releaseInterval;
    	unsigned int numToRelease;
	
};

#endif /*PARTICLESYSTEM_H_*/
