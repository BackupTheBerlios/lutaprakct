#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include "guicomponent.h"
#include "../material/textures/texturemanager.h"

class Window : public GuiComponent{
	
	public:
	
		Window(){tex = NULL; movable = false;};
		virtual ~Window(){};
		
		bool initialize(int height, int width, int x, int y);
		void shutdown();
		
		void setTexture(std::string filename, int repeat);
		
		void draw();
	
		bool isMovable(){return movable;};
		void setMovable(bool m){ movable = m; };
	
	private:
	
		bool movable;
		int width, height;
		texture* tex;
	
};

#endif /*WINDOW_H_*/
