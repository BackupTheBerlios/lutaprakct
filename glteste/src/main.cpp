//#include <SDL/SDL_image.h>

#include <stdlib.h>
#include "util/glext/glextensions.h"
#include "SDL_gpu.h"
#include "GPU_shaders.h"
#include <iostream>
#include <windows.h>
#include "framebuffer.h"


int main(int argc, char **argv)
{
	SDL_Surface *screen;
	SDL_Event event;
	int quit = 0;
	SDL_Rect dest;
	dest.x = 62;
	dest.y = 0;
	struct GPU_Glsprite *glsprite;
	struct GPU_Glsprite *glsprite2;	
	struct GPU_GlShader *shader;
	struct GPU_Framebuffer *buffer;
	framebuffer *buffer2 = new framebuffer;

// 1- inicialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
		//exit(-1);
		return 0;
	}
	atexit(SDL_Quit);
//2-Set Opengl attrs
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


//3- initialize screen
	if((screen = SDL_SetVideoMode(800, 600, 0, SDL_OPENGL | SDL_HWSURFACE)) == 0) {
		fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
        //	exit(-1);
        return 0;
	}

  GPU_Init();
	
//	glViewport(0, 0, 800, 600);
//5- continue initializing opengl
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0, 800, 0, 600, -1, 1);
	//gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);

// initialize the glsprite
    SDL_Surface *img =  SDL_LoadBMP("terreno.bmp");
//	SDL_Color colorkey = {0xFF, 0x00, 0xFF, 0};
	if ( (glsprite = (GPU_InitGlsprite(img, 0, TARGET_TEXTURE_2D | FORMAT_RGB | TYPE_UNSIGNED_BYTE))) == 0 ) {
		fprintf(stderr, "Error loading the image file!\n");
		exit(-1);		
	}
        
  buffer2->addTexture( TEXTURE_2D, RGB, INTERNAL_RGB, 0, 512, 512);
  buffer2->initialize();
	shader = GPU_InitShader(0, invertFS);
	GPU_BindShader(shader);
	GLcharARB *log;
	log = GPU_GetShaderLog(shader);
	printf(log);
	free(log);
//	GPU_SendUniform1f(shader, "Alpha", 0.2f);
	GPU_SendTexture(shader, "texture", 0);
	//GPU_SendUniform1f(shader, "desaturate", 1.0);
	//GPU_SendUniform1f(shader, "toning", 1.0);
	//GPU_SendUniform1f(shader, "texsize", 512.0);
	//GPU_SendUniform1f(shader, "scale", 2.0);
	//GPU_SendUniform1f(shader, "numtiles", 40000.0);
	//GPU_SendUniform1f(shader, "edgewidth", 0.1);

	//GPU_BlitSpriteOnFramebuffer(buffer, glsprite,  &dest);
	
   buffer2->bind();
    {
      glViewport(0, 0, 512, 512);

      glClearColor(0, 0, 0, 0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
      glBindTexture(GL_TEXTURE_2D, glsprite->texID);
      glEnable(GL_TEXTURE_2D);
		
	  glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();
		
      glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex3f(-1, -1, -0.5f);
            glTexCoord2f(1, 0); glVertex3f( 1, -1, -0.5f);
            glTexCoord2f(1, 1); glVertex3f( 1,  1, -0.5f);
            glTexCoord2f(0, 1); glVertex3f(-1,  1, -0.5f);
     glEnd();
     

     glPopMatrix();
    
    }
	buffer2->unbind();
	
	GPU_UnbindShader();
	
		
	SDL_Surface *surface;
	Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 512, 512, 24, rmask, gmask, bmask, 0);
	if(surface == NULL) {
		return 0;
	}

	buffer2->bind();
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glReadPixels(0, 0, 512, 512, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	}
	buffer2->unbind();
	
    //img2 = GPU_FramebufferToSurface(buffer);

	SDL_SaveBMP(surface, "TerrainWithShader.bmp" );
/*
	if ( (glsprite2 = (GPU_InitGlsprite(img2, 0, TARGET_TEXTURE_2D | FORMAT_RGB | TYPE_UNSIGNED_BYTE))) == 0 ) {
		fprintf(stderr, "Error loading the image file 2!\n");
		exit(-1);		
	}
*/	
//	GPU_FreeFramebuffer(buffer);
//	free(buffer);
		
	//buffer2 = GPU_FramebufferInit( TARGET_TEXTURE_2D | FORMAT_RGB | TYPE_UNSIGNED_BYTE, img->w, img->h );
	
/*	shader2 = GPU_ShaderInit(0, brightnessShader);
	GPU_SendTexture(shader2, "texture", 0);	
	//GPU_AddShader(buffer, shader2);
	glUseProgramObjectARB( shader2->program);
	GPU_BlitOnFramebuffer(buffer, glsprite2,  &dest);
	glUseProgramObjectARB( 0);

	if ( (glsprite3 = (GPU_AllocGlsprite(GPU_FramebufferToSurface(buffer), 0, TARGET_TEXTURE_2D | FORMAT_RGB | TYPE_UNSIGNED_BYTE))) == 0 ) {
		fprintf(stderr, "Error loading the image file!\n");
		exit(-1);		
	}


 
/* main loop */
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ){
				case SDLK_ESCAPE:
				case SDLK_q:
					quit = 1;
					break;
				case SDLK_F1:
					SDL_WM_ToggleFullScreen(screen);
					break;
				default:
					break;
				}
			}
		}


		 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GPU_DrawGlsprite(glsprite, 0);
//		GPU_BlitFramebufferOnScreen(buffer, glsprite,  &dest);		
    	
		glFlush();
		SDL_GL_SwapBuffers();
	}

//	SDL_SaveBMP(GPU_FramebufferToSurface(buffer), "buffer2shaders.bmp" );
	
// quit
    GPU_FreeGlsprite(glsprite);
	delete buffer2;
    GPU_FreeShader(shader);
	SDL_Quit();
	return 0;	
}
