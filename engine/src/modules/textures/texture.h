#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../../util/image/image.h"
#include <GL/gl.h>
#include <GL/glext.h>

#include <string>

//TODO fazer texture 3d

class texture{
	
public:

    enum{
		RGB                    = 1 << 0,
		RGBA                   = 1 << 1,
		BGR                    = 1 << 2,
		BGRA                   = 1 << 3,
		
		CLAMP                  = 1 << 4,
		CLAMP_TO_EDGE          = 1 << 5,
		
		NEAREST                = 1 << 6,
		LINEAR                 = 1 << 7,
        NEAREST_MIPMAP_NEAREST = 1 << 8,
		NEAREST_MIPMAP_LINEAR  = 1 << 9,
		LINEAR_MIPMAP_NEAREST  = 1 << 10,
		LINEAR_MIPMAP_LINEAR   = 1 << 11,
		
		ANISOTROPIC_2          = 1 << 12,
		ANISOTROPIC_4          = 1 << 13,
		ANISOTROPIC_8          = 1 << 14,
		ANISOTROPIC_16	       = 1 << 15,
		
		COMPRESSION_ARB        = 1 << 16,
		COMPRESSION_DXT1       = 1 << 17,
		COMPRESSION_DXT3       = 1 << 18,
		COMPRESSION_DXT5       = 1 << 19
	};

	enum {
		TEXTURE_1D          = GL_TEXTURE_1D,
		TEXTURE_2D          = GL_TEXTURE_2D,
		TEXTURE_3D          = GL_TEXTURE_3D, 
		TEXTURE_CUBEMAP     = GL_TEXTURE_CUBE_MAP,
		TEXTURE_RECTANGLE   = GL_TEXTURE_RECTANGLE_ARB,
		TEXTURE_RECTANGLENV = GL_TEXTURE_RECTANGLE_NV
	};

    texture(char* filename, int target, int flags);
    ~texture();
    
	bool load(char* filename, int target, int flags);
	void enable();
	void disable();
	void bind();
	void unload();
	int getWidth(){return img->getWidth();}
	int getHeight(){return img->getHeight();}
	std::string name;
	
private:

	image *img;

	GLuint id;
	GLuint target;
	GLuint format, internalformat;
	int flags;
	
};

#endif //_TEXTURE_H_
