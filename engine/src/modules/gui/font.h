#ifndef FONT_H_
#define FONT_H_

#include <string>
#include "../material/textures/texturemanager.h"


class Font{
	
	public:
	
		Font();
		Font(std::string filename);
		virtual ~Font();
		
		bool initialize(std::string filename);
		void shutdown();
		
		void print(int x, int y, int set, const char* text, ... );
		
	private:
		
		texture* fontTexture;
		float color[4];
		int position[2];
		int listID;
	
};


#endif /*FONT_H_*/
