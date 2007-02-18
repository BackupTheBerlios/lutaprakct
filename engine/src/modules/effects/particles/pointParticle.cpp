
#include "pointParticle.h"
#include "../../../util/glhelper/glextensions.h"
#include <GL/gl.h>

void PointParticle::render(){
	
	//TODO alguams dessas funcoes sao de inicializacao do opengl
	//e devem ficar em outro local
	float quadratic[] =  { 1.0f, 0.0f, 0.01f };
	glPointParameterfvARB( GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic );
    glPointParameterfARB( GL_POINT_FADE_THRESHOLD_SIZE_ARB, 60.0f );
    glPointParameterfARB( GL_POINT_SIZE_MIN_ARB, 1.0f );
    glPointParameterfARB( GL_POINT_SIZE_MAX_ARB, 100.0f );

    glTexEnvf( GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE );
    glEnable( GL_POINT_SPRITE_ARB );
    glPointSize( size );
	
	glBegin( GL_POINTS );
		glColor4f( color[0], color[1], color[2], 1 - fade / life);
		glVertex3f( position[0], position[1], position[2] );
	glEnd();

	glDisable( GL_POINT_SPRITE_ARB );

};
