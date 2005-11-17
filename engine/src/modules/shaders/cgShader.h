#ifndef _CGSHADER_H_
#define _CGSHADER_H_

#include <Cg/cg.h>
#include <Cg/cgGL.h>
/* interface basica para shader em Cg
 */

//TODO adicionar mais profiles na enum
//TODO verificar o caso dos profiles e kill 
//TODO verificar o unbind() para parar o program

enum {
	PROFILE_ARBVP1 = 1,
	PROFILE_ARBFP1
	
};

class cgShader{
	
public:

	cgShader(char *vertexfile, int vertex, char * fragmentfile, int fragment) { initialize(vertexfile, vertex, fragmentfile , fragment); };
	virtual ~cgShader() { kill(); };
	
	bool initialize(char *vertexfile, int vertex, char * fragmentfile, int fragment );
	void kill();
	void bind();
	void unbind();
	virtual void setInitialParameters() = 0;
	virtual void setLoopParameters() = 0;


private:
	bool hasfrag, hasvertex;
	CGcontext context;
	CGprogram vertexprogram, fragmentprogram;
	CGprofile vertexprofile, fragmentprofile;
	
};

#endif //_CGSHADER_H_
