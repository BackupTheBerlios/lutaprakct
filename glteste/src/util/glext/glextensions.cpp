#include "glextensions.h"
#include <string>
#ifndef _WIN32
#include <GL/glx.h>
#endif

//point sprite
PFNGLPOINTPARAMETERFARBPROC glPointParameterfARB;
PFNGLPOINTPARAMETERFVARBPROC glPointParameterfvARB;

//multi texture

PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;

//framebuffer

PFNGLISRENDERBUFFEREXTPROC glIsRenderbufferEXT;
PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT;
PFNGLDELETERENDERBUFFERSEXTPROC glDeleteRenderbuffersEXT;
PFNGLGENRENDERBUFFERSEXTPROC  glGenRenderbuffersEXT;
PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT;
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC glGetRenderbufferParameterivEXT;
PFNGLISFRAMEBUFFEREXTPROC glIsFramebufferEXT;
PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT;
PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT;
PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetFramebufferAttachmentParameterivEXT;
PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmapEXT;

//GLSL
PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB;
PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
PFNGLATTACHOBJECTARBPROC glAttachObjectARB;
PFNGLDELETEOBJECTARBPROC glDeleteObjectARB;
PFNGLBINDATTRIBLOCATIONARBPROC glBindAttribLocationARB;
PFNGLLINKPROGRAMARBPROC glLinkProgramARB;
PFNGLGETINFOLOGARBPROC glGetInfoLogARB;
PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
PFNGLVALIDATEPROGRAMARBPROC glValidateProgramARB;
PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB;
PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB;
PFNGLUNIFORM1IARBPROC glUniform1iARB;
PFNGLUNIFORM1FARBPROC glUniform1fARB;
PFNGLUNIFORM1FVARBPROC glUniform1fvARB;
PFNGLUNIFORM1IVARBPROC glUniform1ivARB;
PFNGLUNIFORM2IARBPROC glUniform2iARB;
PFNGLUNIFORM2FARBPROC glUniform2fARB;
PFNGLUNIFORM2FVARBPROC glUniform2fvARB;
PFNGLUNIFORM2IVARBPROC glUniform2ivARB;
PFNGLUNIFORM3IARBPROC glUniform3iARB;
PFNGLUNIFORM3FARBPROC glUniform3fARB;
PFNGLUNIFORM3FVARBPROC glUniform3fvARB;
PFNGLUNIFORM3IVARBPROC glUniform3ivARB;
PFNGLUNIFORM4IARBPROC glUniform4iARB;
PFNGLUNIFORM4FARBPROC glUniform4fARB;
PFNGLUNIFORM4FVARBPROC glUniform4fvARB;
PFNGLUNIFORM4IVARBPROC glUniform4ivARB;
PFNGLUNIFORMMATRIX2FVARBPROC glUniformMatrix2fvARB;
PFNGLUNIFORMMATRIX3FVARBPROC glUniformMatrix3fvARB;
PFNGLUNIFORMMATRIX4FVARBPROC glUniformMatrix4fvARB;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB;
PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB;

void initializeExtensions() {

#ifdef _WIN32
#define GET_PROC_ADDRESS(a,b) b = (a)wglGetProcAddress(#b)
#else
#define GET_PROC_ADDRESS(a,b) b = (a)glXGetProcAddressARB((const GLubyte*)#b)
#endif

	GET_PROC_ADDRESS(PFNGLPOINTPARAMETERFARBPROC, glPointParameterfARB);
	GET_PROC_ADDRESS(PFNGLPOINTPARAMETERFVARBPROC, glPointParameterfvARB);

	GET_PROC_ADDRESS(PFNGLMULTITEXCOORD2FARBPROC, glMultiTexCoord2fARB);
	GET_PROC_ADDRESS(PFNGLACTIVETEXTUREARBPROC, glActiveTextureARB);
	GET_PROC_ADDRESS(PFNGLCLIENTACTIVETEXTUREARBPROC, glClientActiveTextureARB);

	GET_PROC_ADDRESS(PFNGLCREATEPROGRAMOBJECTARBPROC,glCreateProgramObjectARB);
	GET_PROC_ADDRESS(PFNGLCREATESHADEROBJECTARBPROC,glCreateShaderObjectARB);
	GET_PROC_ADDRESS(PFNGLSHADERSOURCEARBPROC,glShaderSourceARB);
	GET_PROC_ADDRESS(PFNGLCOMPILESHADERARBPROC,glCompileShaderARB);
	GET_PROC_ADDRESS(PFNGLATTACHOBJECTARBPROC,glAttachObjectARB);
	GET_PROC_ADDRESS(PFNGLDELETEOBJECTARBPROC,glDeleteObjectARB);
	GET_PROC_ADDRESS(PFNGLBINDATTRIBLOCATIONARBPROC,glBindAttribLocationARB);
	GET_PROC_ADDRESS(PFNGLLINKPROGRAMARBPROC,glLinkProgramARB);
	GET_PROC_ADDRESS(PFNGLGETINFOLOGARBPROC,glGetInfoLogARB);
	GET_PROC_ADDRESS(PFNGLGETOBJECTPARAMETERIVARBPROC,glGetObjectParameterivARB);
	GET_PROC_ADDRESS(PFNGLVALIDATEPROGRAMARBPROC,glValidateProgramARB);
	GET_PROC_ADDRESS(PFNGLUSEPROGRAMOBJECTARBPROC,glUseProgramObjectARB);
	GET_PROC_ADDRESS(PFNGLGETUNIFORMLOCATIONARBPROC,glGetUniformLocationARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM1IARBPROC,glUniform1iARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM1FARBPROC,glUniform1fARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM1FVARBPROC,glUniform1fvARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM1IVARBPROC,glUniform1ivARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM2IARBPROC, glUniform2iARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM2FARBPROC,glUniform2fARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM2FVARBPROC,glUniform2fvARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM2IVARBPROC,glUniform2ivARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM3IARBPROC, glUniform3iARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM3FARBPROC,glUniform3fARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM3FVARBPROC,glUniform3fvARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM3IVARBPROC,glUniform3ivARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM4IARBPROC, glUniform4iARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM4FARBPROC,glUniform4fARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM4FVARBPROC,glUniform4fvARB);
	GET_PROC_ADDRESS(PFNGLUNIFORM4IVARBPROC,glUniform4ivARB);
	GET_PROC_ADDRESS(PFNGLUNIFORMMATRIX2FVARBPROC,glUniformMatrix2fvARB);
	GET_PROC_ADDRESS(PFNGLUNIFORMMATRIX3FVARBPROC,glUniformMatrix3fvARB);
	GET_PROC_ADDRESS(PFNGLUNIFORMMATRIX4FVARBPROC,glUniformMatrix4fvARB);
	GET_PROC_ADDRESS(PFNGLENABLEVERTEXATTRIBARRAYARBPROC,glEnableVertexAttribArrayARB);
	GET_PROC_ADDRESS(PFNGLDISABLEVERTEXATTRIBARRAYARBPROC,glDisableVertexAttribArrayARB);
	GET_PROC_ADDRESS(PFNGLVERTEXATTRIBPOINTERARBPROC,glVertexAttribPointerARB);
	
	GET_PROC_ADDRESS(PFNGLISRENDERBUFFEREXTPROC, glIsRenderbufferEXT);
	GET_PROC_ADDRESS(PFNGLBINDRENDERBUFFEREXTPROC, glBindRenderbufferEXT);
	GET_PROC_ADDRESS(PFNGLDELETERENDERBUFFERSEXTPROC, glDeleteRenderbuffersEXT);
	GET_PROC_ADDRESS(PFNGLGENRENDERBUFFERSEXTPROC,  glGenRenderbuffersEXT);
	GET_PROC_ADDRESS(PFNGLRENDERBUFFERSTORAGEEXTPROC, glRenderbufferStorageEXT);
	GET_PROC_ADDRESS(PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC, glGetRenderbufferParameterivEXT);
	GET_PROC_ADDRESS(PFNGLISFRAMEBUFFEREXTPROC, glIsFramebufferEXT);
	GET_PROC_ADDRESS(PFNGLBINDFRAMEBUFFEREXTPROC, glBindFramebufferEXT);
	GET_PROC_ADDRESS(PFNGLDELETEFRAMEBUFFERSEXTPROC, glDeleteFramebuffersEXT);
	GET_PROC_ADDRESS(PFNGLGENFRAMEBUFFERSEXTPROC, glGenFramebuffersEXT);
	GET_PROC_ADDRESS(PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC, glCheckFramebufferStatusEXT);
	GET_PROC_ADDRESS(PFNGLFRAMEBUFFERTEXTURE1DEXTPROC, glFramebufferTexture1DEXT);
	GET_PROC_ADDRESS(PFNGLFRAMEBUFFERTEXTURE2DEXTPROC, glFramebufferTexture2DEXT);
	GET_PROC_ADDRESS(PFNGLFRAMEBUFFERTEXTURE3DEXTPROC, glFramebufferTexture3DEXT);
	GET_PROC_ADDRESS(PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC, glFramebufferRenderbufferEXT);
	GET_PROC_ADDRESS(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC, glGetFramebufferAttachmentParameterivEXT);
	GET_PROC_ADDRESS(PFNGLGENERATEMIPMAPEXTPROC , glGenerateMipmapEXT);
	
#undef GET_PROC_ADDRESS
}

bool haveExtension(const char* extension)
{
	const GLubyte *extensions;
	const GLubyte *start;
	GLubyte *where, *terminator;
	
	where = (GLubyte *) strchr(extension, ' ');
	if (where || *extension == '\0' )
		return false;
	
	extensions = glGetString(GL_EXTENSIONS);
	start = extensions;
	for (;;){
		where = (GLubyte *) strstr((const char*) start, extension);
		if (!where)
			break;
		terminator = where + strlen(extension);
		if (where == start || *(where - 1) == ' ')
			if (*terminator == ' ' || *terminator == '\0')
				return true;
		start = terminator;
	}
	return false;
}
