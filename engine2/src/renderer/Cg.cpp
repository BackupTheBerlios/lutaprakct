
#include "Cg.h"
#include <cstdio>

int Cg::initialize(){
	
	cgContext = cgCreateContext();
	if(cgContext == NULL){
		return FAILED_CONTEXT_CREATION;
	}

	cgGLRegisterStates(cgContext);
	
	cgVertexProfile   = cgGLGetLatestProfile(CG_GL_VERTEX);  
	cgFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);

	if(cgVertexProfile == CG_PROFILE_UNKNOWN || cgFragmentProfile == CG_PROFILE_UNKNOWN){
		return INVALID_PROFILE;
	}
	 
	cgGLSetOptimalOptions(cgVertexProfile);
	cgGLSetOptimalOptions(cgFragmentProfile);
	
	if ( !checkErrors() )
		return GENERIC_ERROR;

	return 1; 
	
}

void Cg::shutdown(){
	cgDestroyContext(cgContext);
	cgContext = NULL;
}

bool Cg::checkErrors(){
	CGerror Error = cgGetError();

	if ( Error != CG_NO_ERROR ){    
		printf( "**** Cg Error %s ***** \n", (char *)cgGetErrorString(Error));
		return false; 
	}
	
	return true;
}

void Cg::enableProfiles(){
	cgGLEnableProfile(cgVertexProfile);	
	cgGLEnableProfile(cgFragmentProfile); 
}

void Cg::disableProfiles(){
	cgGLDisableProfile(cgVertexProfile);	
	cgGLDisableProfile(cgFragmentProfile);	
}
