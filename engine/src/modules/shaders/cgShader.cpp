
#include "cgShader.h"

void cgShader::kill(){
	
	if (hasvertex)
		cgDestroyProgram(vertexprogram);
		
	if (hasfrag)
		cgDestroyProgram(fragmentprogram);
	
}

void cgShader::bind(){

	if (hasvertex){
		cgGLEnableProfile(vertexprofile);
		cgGLBindProgram(vertexprogram);
	}
	
	if (hasfrag){
		cgGLEnableProfile(fragmentprofile);
		cgGLBindProgram(fragmentprogram);
	}
	
}

void cgShader::unbind(){

	if(hasvertex){
		cgGLDisableProfile(vertexprofile);
	}
	
	if (hasfrag){
		cgGLDisableProfile(fragmentprofile);
	}
	
}

bool cgShader::initialize(char* vertexfile, int vertex, char * fragmentfile, int fragment){

	context = cgCreateContext();
	
	if (vertex == PROFILE_ARBVP1){
		vertexprofile = CG_PROFILE_ARBVP1;
	}else{
		return false;
	}
		
	if (vertex == PROFILE_ARBFP1){
		fragmentprofile = CG_PROFILE_ARBFP1;
	}else{
		return false;
	}	
	
	if (vertexfile){
		hasvertex = true;
		vertexprogram = cgCreateProgramFromFile(context, CG_SOURCE, vertexfile, vertexprofile, NULL, NULL);
		if (!cgIsProgramCompiled(vertexprogram))
			cgCompileProgram(vertexprogram);

		cgGLEnableProfile(vertexprofile);
		cgGLLoadProgram(vertexprogram);
	}
	
	if (fragmentfile){
		hasfrag = true;
		fragmentprogram = cgCreateProgramFromFile(context, CG_SOURCE, fragmentfile, fragmentprofile, NULL, NULL);
		if (!cgIsProgramCompiled(fragmentprogram))
			cgCompileProgram(fragmentprogram);

		cgGLEnableProfile(fragmentprofile);
		cgGLLoadProgram(fragmentprogram);
	}
	
	return true;
}
