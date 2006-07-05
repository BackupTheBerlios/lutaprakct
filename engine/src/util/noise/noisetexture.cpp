
#include "noise.h"
#include "noisetexture.h"
#include "../glext/glextensions.h"
#include <cstdlib>
#include <iostream>

int noise3DTexSize = 128;
GLuint noise3DTexName = 0;
GLubyte* noise3DTexPtr;

void make3DNoiseTexture(void){

	int f, i, j, k, inc;
	f = i = j = k = inc = 0;
	int startFrequency = 4;
	int numOctaves = 4;
	double ni[3];
	double inci, incj, inck;
	int frequency = startFrequency;
	GLubyte* ptr;
	double amp = 0.5;
	
	noise3DTexPtr = (GLubyte*) malloc (noise3DTexSize * noise3DTexSize * noise3DTexSize * 4);

	std::cout << "Criando tetxura Noise 3D" << std::endl;	
	for ( f = 0, inc = 0; f < numOctaves; ++f, frequency *= 2, ++inc, amp *= 0.5){
		SetNoiseFrequency(frequency);
		ptr = noise3DTexPtr;
		ni[0] = ni[1] = ni[2] = 0;
		
		inci = 1.0 / (noise3DTexSize / frequency);

		for (i = 0; j < noise3DTexSize; ++i, ni[0] += inc ){
			incj = 1.0 / (noise3DTexSize / frequency );		
			for( j = 0; j < noise3DTexSize; ++j, ni[1] += incj){
				inck = 1.0 / (noise3DTexSize / frequency );
				for (k = 0; k < noise3DTexSize; ++k, ni[2] +=inck, ptr+=4){
					GLubyte valor = 0;
					for( int a = 0; a < 1000; a++){
						valor += (((noise3(ni)+1.0)*amp/a)*128.0);
						//*(ptr+inc) = (GLubyte) (((noise3(ni)+1.0)*amp)*128.0) + (((noise3(ni)+1.0)*amp/2.0)*128.0);
					}
					*(ptr+inc) = (GLubyte) valor;
				}
				
			}
			
		}
	}
	
}

GLuint init3DNoiseTexture(){
	
	std::cout << "Criando tetxura 3D" << std::endl;
	make3DNoiseTexture();

    glGenTextures(1, &noise3DTexName);
    glBindTexture(GL_TEXTURE_3D, noise3DTexName);

    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       
    glTexImage3DEXT(GL_TEXTURE_3D, 0, GL_RGBA, noise3DTexSize, noise3DTexSize, noise3DTexSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, noise3DTexPtr);
    
    return noise3DTexName;
       
}
