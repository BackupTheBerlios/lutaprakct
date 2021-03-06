#ifndef _SDL_GPU_H_
#define _SDL_GPU_H_

#include "SDL/SDL.h"
#include "util/glext/glextensions.h"

/* USO:
 * 1- Initialize SDL
 * 2- Set OpenGL attrs
 * 3- SInitialize screen
 * 4- Initialize SDL_gpu
 * 5- Continue seting Opengl
 */

struct GPU_Glsprite {
	unsigned int texID;
	SDL_Rect rect;
	GLenum textarget;
	GLint internalformat;
	GLenum format;
	GLenum type;
	int textureflags;
	int sizex, sizey;
	//SDL_Surface *image;
};

typedef struct GPU_Glsprite GPU_glsprite;

struct GPU_Framebuffer{
	GLuint framebufferID;  // color render target
	GLuint depthbufferID; // depth render target
	GLuint texID; // texture
	GLenum textarget;
	int textureflags;
	int sizex, sizey;
	int ntex;
	
	unsigned int numshaders;
	struct GPU_GlShader **shaders;
};

struct GPU_GlShader{
	
	int shadertype;
	GLhandleARB fragment, vertex, program;
	
};

enum { TARGET_TEXTURE_2D = 1 << 0,
	   TARGET_TEXTURE_RECT = 1 << 1,
	   TARGET_TEXTURE_CUBEMAP = 1 << 2,
	   
	   FORMAT_RGB = 1 << 3,
	   FORMAT_RGBA = 1 << 4,
	   
	   TYPE_UNSIGNED_BYTE = 1 << 5,
	   TYPE_FLOAT = 1 << 6,
	   
	   CLAMP_TO_EDGE = 1 << 7,
   	   CLAMP = 1 << 8,
   	   REPEAT = 1 << 9,
   	   
   	   INTERNAL_FORMAT_BGR = 1 << 10,
   	   INTERNAL_FORMAT_BGRA = 1 << 11,
   	   INTERNAL_FORMAT_RGB = 1 << 12,
   	   INTERNAL_FORMAT_RGBA = 1 << 13
};

enum { 
   	   INTERNAL_BGR = 1,
   	   INTERNAL_BGRA = 2,
   	   INTERNAL_RGB = 3,
   	   INTERNAL_RGBA = 4
		};
		
enum {
	   RGB = 1,
	   RGBA = 2,
		};

enum {
		 TEXTURE_2D = 1 ,
	   TEXTURE_RECT_ARB = 2,
		 TEXTURE_CUBEMAP = 3,
	   TEXTURE_RECT_NV = 4
	}; 
	

void GPU_PrintGLErrors( );

int GPU_QueryExtension(char *extname);
int GPU_Init();

/*shader functions*/
struct GPU_GlShader* GPU_InitShader(const char *vertex, const char* fragment);
int GPU_SendTexture(struct GPU_GlShader *shader, char * texname, unsigned int position);
int GPU_SendUniform1f(struct GPU_GlShader *shader, char *uniform, float value);
GLcharARB* GPU_GetShaderLog(struct GPU_GlShader *shader);
void GPU_FreeShader(struct GPU_GlShader *shader);
void GPU_BindShader(struct GPU_GlShader *shader);
void GPU_UnbindShader();

/*framebuffer functions*/
//struct GPU_Framebuffer *GPU_InitFramebuffer(int textureflags, int sizex, int sizey);
int GPU_InitFramebuffer(struct GPU_Framebuffer *buf, int textureflags, int sizex, int sizey);
void GPU_FreeFramebuffer(struct GPU_Framebuffer *buf);
void GPU_BlitFramebufferOnScreen(struct GPU_Framebuffer *buf, struct GPU_Glsprite *sprite, SDL_Rect *dest);
void GPU_BlitSpriteOnFramebuffer(struct GPU_Framebuffer *buf, struct GPU_Glsprite *sprite, SDL_Rect *dest);
SDL_Surface* GPU_FramebufferToSurface(struct GPU_Framebuffer *buf);
char* GPU_GetFrameBufferStatus();

/*sprite functions*/
struct GPU_Glsprite *GPU_InitGlsprite(SDL_Surface *pixels, SDL_Color *colorkey, int textureflags);
void GPU_DrawGlsprite( struct GPU_Glsprite *sprite, SDL_Rect *dest );
int GPU_FreeGlsprite( struct GPU_Glsprite *sprite);

#endif //_SDL_GPU_H_
