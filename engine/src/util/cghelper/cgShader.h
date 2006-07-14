#ifndef _CGSHADER_H_
#define _CGSHADER_H_

#include <Cg/cg.h>
#include <Cg/cgGL.h>

#include "../../modules/material/materialData.h"

/* interface basica para shader em Cg
 */

//TODO adicionar mais profiles na enum
//TODO verificar o caso dos profiles e kill 
//TODO verificar o unbind() para parar o program

enum {
	PROFILE_ARBVP1 = 1,
	PROFILE_ARBFP1,
	PROFILE_VP40,
	PROFILE_FP40
	
};

enum {
	AUTOCOMPILE_MANUAL = 1 << 1,
	TESTE = 1 << 2
	
};

class cgShader{
	
public:

	cgShader(){};
	cgShader(char *vertexfile, int vertex, char * fragmentfile, int fragment, int flags) { initialize(vertexfile, vertex, fragmentfile , fragment, flags); };
	virtual ~cgShader() { kill(); };
	
	bool initialize(char *vertexfile, int vertex, char * fragmentfile, int fragment, int flags );
	void kill();
	void bind();
	void unbind();
	void compile();
	virtual void setInitialParameters(materialData *config) = 0;
	virtual void setLoopParameters(materialData *config) = 0;

	CGcontext getContext(){return context; };

protected:
	bool hasfrag, hasvertex;
	CGcontext context;
	CGprogram vertexprogram, fragmentprogram;
	CGprofile vertexprofile, fragmentprofile;
	
};

#endif //_CGSHADER_H_
