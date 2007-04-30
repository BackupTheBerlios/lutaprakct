#ifndef CGATMOSPHERIC_H_
#define CGATMOSPHERIC_H_

#include "../../../util/cghelper/cgShader.h"

class CgAtmospheric : public CgShader{
	
	public:
	
	CgAtmospheric(){};
	CgAtmospheric(char *vertexfile, int vertex, char * fragmentfile, int fragment, int flags ) { initialize(vertexfile,  vertex,  fragmentfile,  fragment, flags); };
	virtual ~CgAtmospheric(){kill();};

	virtual void setInitialParameters(void* config){
		
		modelViewProj = cgGetNamedParameter(vertexprogram, "worldViewProj");
		modelView = cgGetNamedParameter(vertexprogram, "worldView");
		
	};
	virtual void setLoopParameters(void* config){
		cgGLSetStateMatrixParameter(modelViewProj, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
		cgGLSetStateMatrixParameter(modelView, CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_IDENTITY);
	};

	CGparameter modelViewProj;
	CGparameter modelView;
	
};

#endif /*CGATMOSPHERIC_H_*/
