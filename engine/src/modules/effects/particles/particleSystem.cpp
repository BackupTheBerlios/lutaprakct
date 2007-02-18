
#include "particleSystem.h"

ParticleSystem::ParticleSystem(InitializePolicy* colorinit, InitializePolicy* sizeinit, InitializePolicy* velocityinit, InitializePolicy* lifeinit, InitializePolicy* positioninit, InitializePolicy* forceinit, ActionPolicy* coloraction, ActionPolicy* sizeaction, ActionPolicy* velocityaction, ActionPolicy* lifeaction, ActionPolicy* positionaction, ActionPolicy* forceaction ){
			
		initPolicy = new SimpleInitializePolicy(colorinit, sizeinit, velocityinit, lifeinit, positioninit, forceinit);
		actionPolicy = new SimpleActionPolicy(coloraction, sizeaction, velocityaction, lifeaction, positionaction, forceaction);	
};
