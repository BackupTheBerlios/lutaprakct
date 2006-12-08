#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include "guicomponent.h"
#include "../material/textures/texturemanager.h"

class WindowImage : public GuiComponent{
	
	public:
	
		WindowImage(){tex = NULL; movable = false;};
		virtual ~WindowImage(){};
		
		bool initialize(int height, int width, int x, int y, bool useAlpha);
		void shutdown();
		
		void setTexture(std::string filename);
		void setBorder(std::string toptex, std::string bottomtex, std::string righttex, std::string lefttex, std::string toprightex, std::string toplefttex, std::string bottomrighttex, std::string bottomlefttex, int bordersize);
		
		void draw();
	
		bool isMovable(){return movable;};
		void setMovable(bool m){ movable = m; };
		
		bool hasAlpha(){ return alpha; };
		void setAlpha(bool a){ alpha = a; };
	
	private:
	
		void drawBorder();
	
		bool movable;
		bool alpha;
		int width, height;
		int bordersize;
		texture* tex;
		texture* toptex;
		texture* bottomtex;
		texture* righttex;
		texture* lefttex;
		texture* toprightex;
		texture* toplefttex;
		texture* bottomrighttex;
		texture* bottomlefttex;
	
};

#endif /*WINDOW_H_*/
