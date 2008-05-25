#ifndef CG_H_
#define CG_H_

#include <Cg/cg.h>
#include <Cg/cgGL.h>

enum{
	FAILED_CONTEXT_CREATION = -1,
	INVALID_PROFILE = -2,
	GENERIC_ERROR = -3
};

/* classe responsavel pelos shaders em Cg, eh um subsitema do render */

const int	CrtFragmentProgram = 1;
const int	CrtVertexProgram = 0; 
const int	MAX_SKIN_JOINTS = 80; 
const int	MAX_NBR_PROGRAMS = 10; 

class Cg{
	
public:
	
	int initialize();
	void shutdown();
	void enableProfiles();
	void disableProfiles();
	bool checkErrors();
	
	CGprogram	cgPrograms[MAX_NBR_PROGRAMS];
	CGprofile	cgVertexProfile, cgFragmentProfile;
	CGcontext	cgContext;
	
};

#endif /*CG_H_*/
