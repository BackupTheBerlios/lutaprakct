#ifndef NOISETEXTURE_H_
#define NOISETEXTURE_H_

#include<GL/gl.h>
#include<GL/glu.h>

int noise3DTexSize = 128;
GLuint noise3DTexName = 0;
GLubyte* noise3DTexPtr;

void make3DNoiseTexture(void);
void init3DNoiseTexture();

#endif /*NOISETEXTURE_H_*/
