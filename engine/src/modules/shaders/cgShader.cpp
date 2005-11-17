
#include "cgShader.h"

bool cgShader::initialize(char* vertexfile, CGprofile vertex, char * fragmentfile, CGprofile fragment){

	context = cgCreateContext();
	if (cgGLIsProfileSupported(vertex))
		vertexprofile = vertex;
	else
		return false;
		
	if (cgGLIsProfileSupported(fragment))
		fragmentprofile = fragment;
	else
		return false;	
	
	if (vertexfile){
		vertexprogram = cgCreateProgramFromFile(context, CG_SOURCE, vertexfile, vertexprofile, NULL, NULL);
		if (!cgIsProgramCompiled(vertexprogram))
			cgCompileProgram(vertexprogram);

		cgGLEnableProfile(vertexprofile);
		cgGLLoadProgram(vertexprogram);
	}
	
	if (fragmentfile){
		fragmentprogram = cgCreateProgramFromFile(context, CG_SOURCE, fragmentfile, fragmentprofile, NULL, NULL);
		if (!cgIsProgramCompiled(fragmentprogram))
			cgCompileProgram(fragmentprogram);

		cgGLEnableProfile(fragmentprofile);
		cgGLLoadProgram(fragmentprogram);
	}
	
	
}