#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL/SDL.h>
#include "../events/eventhandler.h"
#include "../util/Singleton.h"
#include "../util/VideoConfig.h"

class Renderer : public EventHandler{
	
	public:
	
		 enum{
		  FULLSCREEN   = 1 << 7,
		  RESIZABLE    = 1 << 10,
		  NOFRAME      = 1 << 11,

		 };

		
		Renderer();
		~Renderer();
		
		bool initialize(VideoConfig& config);
		int initializeOpenGl();
		int initializeSdl(VideoConfig& config);
		void update();
		void stop();
		
		void handleEvent(const event &e);
		
		unsigned int initializeVBO(unsigned int size, const void* data);
		void killVBO(unsigned int vboID);
		void drawVBO(unsigned int vertexID, const void* vertexData, unsigned int vertexCount, 
							unsigned int normalID, const void* normalData);
	private:
		
		int screenShotNumber;
		
		void draw();
		void beginDraw();
		void endDraw();
		
		void setupViewMatrix();
		void setupProjectionMatrix();
		
		SDL_Surface *screen;
		int height, width, bpp, flags;
		float clearcolor[4];
		float znear, zfar, fovy;
};

typedef Singleton<Renderer> RENDERER;

#endif /*RENDERER_H_*/
