#ifndef VIDEOCONFIG_H_
#define VIDEOCONFIG_H_

#include <string>
#include <vector>

struct VideoConfig{
	
	int width;
	int height;
	float fovy, znear, zfar;
	
	int flags;
	
	int redBits, greenBits, blueBits, alphaBits, stencilBits, depthBits;
	
	float clearColor[4];
	
	std::string windowTitle;
	bool showCursor;
	
	std::vector<std::string> glExtensions;
	
};

#endif /*VIDEOCONFIG_H_*/
