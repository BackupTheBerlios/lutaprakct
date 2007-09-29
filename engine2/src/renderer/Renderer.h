#ifndef RENDERER_H_
#define RENDERER_H_

#include "../events/eventhandler.h"
#include "../util/patterns/Singleton.h"

class Renderer : public EventHandler{
	
	public:
	
		Renderer();
		~Renderer();
		
		bool initialize();
		void update();
		void stop();
		
		void handleEvent(const event &e);
		
	private:
		
		void draw();
		void beginDraw();
		void endDraw();
		
		void setupViewMatrix();
		void setupProjectionMatrix();
};

typedef Singleton<Renderer> RENDERER;

#endif /*RENDERER_H_*/
