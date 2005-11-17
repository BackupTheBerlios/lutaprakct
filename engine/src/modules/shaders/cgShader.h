#ifndef _CGSHADER_H_
#define _CGSHADER_H_

#include <Cg/cg.h>
#include <Cg/cgGL.h>
/* interface basica para shader em Cg
 */

class cgShader{
	
public:

	cgShader();
	virtual ~cgShader();
	
	bool initialize(char *vertexfile, CGprofile vertex, char * fragmentfile, CGprofile fragment );
	virtual void bind() = 0;
	virtual void unbind() =0;
	virtual void setParameters() = 0;


private:
	
	CGcontext context;
	CGprogram vertexprogram, fragmentprogram;
	CGprofile vertexprofile, fragmentprofile;
	
};

#endif //_CGSHADER_H_
