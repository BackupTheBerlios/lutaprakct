#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../../../util/image/image.h"
#include <GL/gl.h>
#include <GL/glext.h>

#include <string>

//TODO fazer texture 3d

class texture{
	
public:

    enum{
		CLAMP                  = 1 << 1,
		CLAMP_TO_EDGE          = 1 << 2,
		
		NEAREST                = 1 << 3,
		LINEAR                 = 1 << 4,
        NEAREST_MIPMAP_NEAREST = 1 << 5,
		NEAREST_MIPMAP_LINEAR  = 1 << 6,
		LINEAR_MIPMAP_NEAREST  = 1 << 7,
		LINEAR_MIPMAP_LINEAR   = 1 << 8,
		
		ANISOTROPIC_2          = 1 << 9,
		ANISOTROPIC_4          = 1 << 10,
		ANISOTROPIC_8          = 1 << 11,
		ANISOTROPIC_16	       = 1 << 12,
		
		COMPRESSION_ARB        = 1 << 13,
		COMPRESSION_DXT1       = 1 << 14,
		COMPRESSION_DXT3       = 1 << 15,
		COMPRESSION_DXT5       = 1 << 16,
		
		MIPMAP_SGI			   = 1 << 17
	};
	
	//formats
	enum {
		RGB                    = 1,
		RGBA                   = 2,
		BGR                    = 3,
		BGRA                   = 4,
		LUMINANCE              = 5,
		LUMINANCE_ALPHA        = 6
	};
	//internal formats
	enum {
		RGB8                    = 1,
		RGBA8                   = 2,
		RGB16                   = 3,
		RGBA16                  = 4
	};
	
	//targets
	enum {
		TEXTURE_1D          = GL_TEXTURE_1D,
		TEXTURE_2D          = GL_TEXTURE_2D,
		TEXTURE_3D          = GL_TEXTURE_3D, 
		TEXTURE_CUBEMAP     = GL_TEXTURE_CUBE_MAP,
		TEXTURE_RECTANGLE   = GL_TEXTURE_RECTANGLE_ARB,
		TEXTURE_RECTANGLENV = GL_TEXTURE_RECTANGLE_NV
	};

    texture(char* filename, int target, int format, int internalformat, int flags);
    ~texture();
    
	bool load(char* filename, int target, int format, int internalformat, int flags);
	void enable();
	void disable();
	void bind();
	void unload();
	int getWidth(){return img->getWidth();}
	int getHeight(){return img->getHeight();}
	std::string name;

	image *img;
	
private:


	GLuint id;
	GLuint target;
	GLuint format, internalformat;
	int flags;
	
};

#endif //_TEXTURE_H_
