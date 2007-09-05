#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "Renderer.h"

Renderer::Renderer(){
}

Renderer::~Renderer(){
}

void Renderer::handleEvent(const event& e){
}

bool Renderer::initialize(){
	return true;
}

void Renderer::stop(){
}

void Renderer::update(){
	beginDraw();
	draw();
	endDraw();
}

void Renderer::draw(){
}

void Renderer::beginDraw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
}

void Renderer::endDraw(){
	SDL_GL_SwapBuffers();
}
