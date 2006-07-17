
#include "vbo.h"

Vbo::Vbo(){
}

Vbo::Vbo(int target, int size, void* data, int usage){
	initialize(target, size, data, usage);
}

Vbo::~Vbo(){
	kill();
}

void Vbo::initialize(int target, int size, void* data, int usage){

//	glGenBuffers(size, 	
	
}

void Vbo::kill(){
//	glDeleteBuffersARB(id);
}
