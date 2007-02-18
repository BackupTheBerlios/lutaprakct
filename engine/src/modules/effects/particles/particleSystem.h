#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_

#include "particle.h"
#include <list>

class ParticleSystem{
	
	public:
		
	
	private:
	
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
