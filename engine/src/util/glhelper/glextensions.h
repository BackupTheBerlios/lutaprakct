#ifndef _GLEXTENSIONS_H_
#define _GLEXTENSIONS_H_

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glext.h>


/** esses sao os ponteiros pras extensions do opengl.
*nao tem nada a v com o glext.h do opengl
*/

/**
 * Esse arquivo contem a inicializa?ao das extensions do OpenGL
 * utilizadas na engine. Antes de utilizar as extensions chame
 * a fun?ao que inicializa o video (no caso do sdl a initializa
 * (pois eh chamado sdlInit nela) e entao eh so utilizalas normalmente.
 * 
 * TODO adicionar suporte das extensions pra MAC OS
 */



void initializeExtensions();

bool haveExtension(const char* extension);

/** esses 3 defines deveriam estar no glext.h mas nao estao
 * pode dar problemas em outros pcs.
 */
#define COMPRESSED_RGB_S3TC_DXT1_EXT	0x83F0
#define COMPRESSED_RGBA_S3TC_DXT1_EXT	0x83F1
#define COMPRESSED_RGBA_S3TC_DXT3_EXT	0x83F2
#define COMPRESSED_RGBA_S3TC_DXT5_EXT	0x83F3

//point sprite
extern PFNGLPOINTPARAMETERFARBPROC glPointParameterfARB;
extern PFNGLPOINTPARAMETERFVARBPROC glPointParameterfvARB;

//multi texture

extern PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
extern PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
extern PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;

//texture 3D
extern PFNGLTEXIMAGE3DEXTPROC glTexImage3DEXT;

//GLSL
extern PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB;
extern PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
extern PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
extern PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
extern PFNGLATTACHOBJECTARBPROC glAttachObjectARB;
extern PFNGLDELETEOBJECTARBPROC glDeleteObjectARB;
extern PFNGLBINDATTRIBLOCATIONARBPROC glBindAttribLocationARB;
extern PFNGLLINKPROGRAMARBPROC glLinkProgramARB;
extern PFNGLGETINFOLOGARBPROC glGetInfoLogARB;
extern PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
extern PFNGLVALIDATEPROGRAMARBPROC glValidateProgramARB;
extern PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB;
extern PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB;
extern PFNGLUNIFORM1IARBPROC glUniform1iARB;
extern PFNGLUNIFORM1FARBPROC glUniform1fARB;
extern PFNGLUNIFORM1FVARBPROC glUniform1fvARB;
extern PFNGLUNIFORM1IVARBPROC glUniform1ivARB;
extern PFNGLUNIFORM2IARBPROC glUniform2iARB;
extern PFNGLUNIFORM2FARBPROC glUniform2fARB;
extern PFNGLUNIFORM2FVARBPROC glUniform2fvARB;
extern PFNGLUNIFORM2IVARBPROC glUniform2ivARB;
extern PFNGLUNIFORM3IARBPROC glUniform3iARB;
extern PFNGLUNIFORM3FARBPROC glUniform3fARB;
extern PFNGLUNIFORM3FVARBPROC glUniform3fvARB;
extern PFNGLUNIFORM3IVARBPROC glUniform3ivARB;
extern PFNGLUNIFORM4IARBPROC glUniform4iARB;
extern PFNGLUNIFORM4FARBPROC glUniform4fARB;
extern PFNGLUNIFORM4FVARBPROC glUniform4fvARB;
extern PFNGLUNIFORM4IVARBPROC glUniform4ivARB;
extern PFNGLUNIFORMMATRIX2FVARBPROC glUniformMatrix2fvARB;
extern PFNGLUNIFORMMATRIX3FVARBPROC glUniformMatrix3fvARB;
extern PFNGLUNIFORMMATRIX4FVARBPROC glUniformMatrix4fvARB;

extern PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB;
extern PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB;
extern PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB;


#endif //_GLEXTENSIONS_H_
