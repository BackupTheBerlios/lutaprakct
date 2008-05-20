
#include "Engine.h"
#include "util/Timer.h"
#include "events/input/sdlinputcore.h"
#include "renderer/Renderer.h"
#include "util/tinyxml/tinyxml.h"
#include <iostream>

Engine::Engine(){
	running = true;
}

Engine::~Engine(){
}

/*
 * inicializa coisas basicas da engine: timer, input, janela e renderer
 */
bool Engine::initialize(){
	
	srand((unsigned)time(NULL));
	
	VideoConfig videoConfig; 
	videoConfig.alphaBits = videoConfig.redBits = videoConfig.blueBits = videoConfig.greenBits = videoConfig.stencilBits = 8;
	videoConfig.depthBits = 24;
	videoConfig.clearColor[0] = 0.6; videoConfig.clearColor[1] = 0.6; videoConfig.clearColor[2] = 0.6;
	videoConfig.width = 800; videoConfig.height = 600;
	videoConfig.fovy = 45.0; videoConfig.zfar = 6000.0; videoConfig.znear = 1.0;
	videoConfig.showCursor = false;
	videoConfig.windowTitle = "Engine";
	videoConfig.bpp =  24;
	videoConfig.glExtensions.push_back("GL_ARB_vertex_program");
	videoConfig.glExtensions.push_back("GL_NV_vertex_program");
	videoConfig.glExtensions.push_back("GL_ARB_imaging");
	videoConfig.glExtensions.push_back("GL_ARB_point_parameters");
	videoConfig.glExtensions.push_back("GL_EXT_framebuffer_object");
	videoConfig.glExtensions.push_back("GL_ARB_vertex_buffer_object");
	videoConfig.glExtensions.push_back("GL_ARB_multitexture");
	videoConfig.glExtensions.push_back("GL_EXT_texture3D");
	videoConfig.glExtensions.push_back("GL_ARB_shading_language_100");

	if (!RENDERER::getInstance().initialize(videoConfig)){
		std::cout << "Nao foi possivel inicializar o renderer." << std::endl;
		return false;
	}
	
	if (!TIMER::getInstance().initialize()){//inicializa o sdl timer
		std::cout << "Nao foi possivel inicializar o timer." << std::endl;
		return false;
	}
	
	//inicializa o sdl input, pega a dimensao da janela
	if (!INPUT::getInstance().initialize(videoConfig.width, videoConfig.height)){
		std::cout << "Nao foi possivel inicializar o input." <<std::endl;
		return false;
	}
	
	return true;
}

void Engine::mainLoop(){
	
	while(running){
		TIMER::getInstance().update();
		if (!INPUT::getInstance().update())
			running = false;
		RENDERER::getInstance().update();
	}
	
}

bool Engine::isRunning(){
	return running;
}

void Engine::stop(){
	running = false;
}

//TODO deletar o que foi instanciado
void Engine::shutdown(){
	
}

int main(int argc, char *argv[]){
	
	Engine eng;
	if (!eng.initialize()){
		return 0;
	}
	eng.mainLoop();
	eng.shutdown();
	return 0;
	
}
