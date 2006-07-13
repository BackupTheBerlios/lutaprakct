
#include "cgShader.h"
#include <iostream>

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

void cgShader::compile(){
	
	if (hasvertex){
		if (!cgIsProgramCompiled(vertexprogram)){
			cgCompileProgram(vertexprogram);
			cgCompileProgram(fragmentprogram);
		}
	}
	
	if (hasfrag){
			if (!cgIsProgramCompiled(fragmentprogram)){
				cgGLLoadProgram(vertexprogram);
				cgGLLoadProgram(fragmentprogram);
			}
	}
	
}

bool cgShader::initialize(char* vertexfile, int vertex, char * fragmentfile, int fragment, int flags){

	context = cgCreateContext();
	
	if (vertex == PROFILE_ARBVP1)
		vertexprofile = CG_PROFILE_ARBVP1;
	else if (vertex == PROFILE_VP40)
		vertexprofile == CG_PROFILE_VP30;
	
		
	if (fragment == PROFILE_ARBFP1)
		fragmentprofile = CG_PROFILE_ARBFP1;
	else if (fragment == PROFILE_FP40)
		fragmentprofile = CG_PROFILE_FP30;
	
	if (flags &AUTOCOMPILE_MANUAL)
		cgSetAutoCompile(context, CG_COMPILE_MANUAL);	
	
	if (vertexfile){
		hasvertex = true;
		
		vertexprogram = cgCreateProgramFromFile(context, CG_SOURCE, vertexfile, vertexprofile, NULL, NULL);
		//if (!cgIsProgramCompiled(vertexprogram))
		//	cgCompileProgram(vertexprogram);

		cgGLEnableProfile(vertexprofile);
		
		if (!flags)
			cgGLLoadProgram(vertexprogram);
	}
	
	
	if (fragmentfile){
		hasfrag = true;
		
		fragmentprogram = cgCreateProgramFromFile(context, CG_SOURCE, fragmentfile, fragmentprofile, NULL, NULL);
		//if (!cgIsProgramCompiled(fragmentprogram))
		//	cgCompileProgram(fragmentprogram);
		cgGLEnableProfile(fragmentprofile);
		
		if (!flags)
			cgGLLoadProgram(fragmentprogram);
	}
	return true;
}
