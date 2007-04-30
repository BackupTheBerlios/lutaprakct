#ifndef FONT_H_
#define FONT_H_

#include <string>
#include "../material/textures/texturemanager.h"


class Font{
	
	public:
	
		Font();
		Font(std::string filename);
		virtual ~Font();
		
		bool initialize(std::string& filename);
		void shutdown();
		
		void print(int x, int y, const char* text, ... );
		
		void setColor(float r, float g, float b, float a);
		void setColor(float r, float g, float b);
		void setFontSet(int i);
		void setCharacterWidth(float w);
		void setCharacterHeight(float h);
		void setScale(float x, float y, float z);
		
	private:
		
		Texture* fontTexture;
		float color[4];
		float scale[3];
		float width, height;
		int fontset;
		int listID;
	
};


#endif /*FONT_H_*/
