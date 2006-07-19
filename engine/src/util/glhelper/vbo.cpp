
#include "vbo.h"
#include <iostream>

Vbo::Vbo(){
}

Vbo::Vbo(int target, int size, void* data, int usage){
	initialize(target, size, data, usage);
}

Vbo::~Vbo(){
	kill();
}

void Vbo::initialize(int target, int size, void* data, int usage){

	if (target == ARRAY)
		this->target = GL_ARRAY_BUFFER_ARB;
	else if (target == ELEMENT_ARRAY)
		this->target = GL_ELEMENT_ARRAY_BUFFER_ARB;
		
	if (usage == STATIC_DRAW)
		this->usage = GL_STATIC_DRAW_ARB;
	else if (usage == DYNAMIC_DRAW)
		this->usage = GL_DYNAMIC_DRAW_ARB;
	else if (usage == STREAM_DRAW)
		this->usage = GL_STREAM_DRAW_ARB;

	glGenBuffersARB(1, &id);
	glBindBufferARB(this->target, id);
	glBufferDataARB(this->target, size, data, this->usage);
}

void Vbo::kill(){
	glDeleteBuffersARB(1, &id);
}

void Vbo::unbind(){
	glBindBufferARB(target, 0);		
}

void Vbo::bind(){
	glBindBufferARB(target, id);
}
