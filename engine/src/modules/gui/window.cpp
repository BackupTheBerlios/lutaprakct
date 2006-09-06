
#include "window.h"

void Window::shutdown(){
}

bool Window::initialize(int height, int width, int x, int y){
	
	this->width = width;
	this->height = height;
	position[0] = x;
	position[1] = y;
	
	return true;
}

void Window::setTexture(std::string filename, int repeat){
	
	tex = TEXTUREMANAGER::getInstance().load( const_cast<char*>(filename.c_str()), texture::TEXTURE_2D, texture::RGB, texture::RGB8, 0);
	
}
