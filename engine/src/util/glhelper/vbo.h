#ifndef VBO_H_
#define VBO_H_

#include <GL/gl.h>
#include "glextensions.h"

/* essa classe eh um wraper sobre o vertex buffer object , funciona
 * de maneira semelhante a uma textura
 * */

class Vbo{
	
	public:
	
		Vbo();
		Vbo(int target, int size, void* data, int usage);
		~Vbo();
		
		void bind();
		void unbind();
		void initialize(int target, int size, void* data, int usage);
		void kill();
		
		unsigned int getId(){ return id; };
		
	private:
	
		GLuint id;
	
};


#endif /*VBO_H_*/
