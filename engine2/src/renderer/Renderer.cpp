#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "Renderer.h"
#include "QuatCamera.h"
#include "../video/Video.h"

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

void Renderer::setupViewMatrix(){
	QUATCAMERA::getInstance().setupViewMatrix();
}

void Renderer::setupProjectionMatrix(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const float fAspect = (float)VIDEO::getInstance().getWidth() / (float) VIDEO::getInstance().getHeight();// (const float) (g_nWinWidth) / (const float) (g_nWinHeight);
	gluPerspective(VIDEO::getInstance().getFovy(), fAspect, VIDEO::getInstance().getZnear(), VIDEO::getInstance().getZfar());
}

void Renderer::beginDraw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
}

void Renderer::endDraw(){
	SDL_GL_SwapBuffers();
}
