
#include "frustum.h"
#include <GL/gl.h>
#include <cmath>

enum FrustumPlanes
{
	RIGHT	= 0,	
	LEFT	= 1,		
	BOTTOM	= 2,	
	TOP		= 3,
	BACK	= 4,
	FRONT	= 5
}; 

void Frustum::normalizeFrustumPlane(int side){
	float magnitude = (float)sqrt( planes[side][0] * planes[side][0] + 
								   planes[side][1] * planes[side][1] + 
								   planes[side][2] * planes[side][2] );

	planes[side][0] /= magnitude;
	planes[side][1] /= magnitude;
	planes[side][2] /= magnitude;
	planes[side][3] /= magnitude; 
}

void Frustum::update(){

	//usar o tipo mat4 ao inves desses floats?
	float   proj[16];
	float   modl[16];
	float   clip[16];

	glGetFloatv( GL_PROJECTION_MATRIX, proj );
	glGetFloatv( GL_MODELVIEW_MATRIX, modl );

	clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
	clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
	clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
	clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

	clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
	clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
	clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
	clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

	clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
	clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
	clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];
	

	planes[RIGHT][0] = clip[ 3] - clip[ 0];
	planes[RIGHT][1] = clip[ 7] - clip[ 4];
	planes[RIGHT][2] = clip[11] - clip[ 8];
	planes[RIGHT][3] = clip[15] - clip[12];
	normalizeFrustumPlane( RIGHT);

	planes[LEFT][0] = clip[ 3] + clip[ 0];
	planes[LEFT][1] = clip[ 7] + clip[ 4];
	planes[LEFT][2] = clip[11] + clip[ 8];
	planes[LEFT][3] = clip[15] + clip[12];
	normalizeFrustumPlane( LEFT);

	planes[BOTTOM][0] = clip[ 3] + clip[ 1];
	planes[BOTTOM][1] = clip[ 7] + clip[ 5];
	planes[BOTTOM][2] = clip[11] + clip[ 9];
	planes[BOTTOM][3] = clip[15] + clip[13];
	normalizeFrustumPlane( BOTTOM);

	planes[TOP][0] = clip[ 3] - clip[ 1];
	planes[TOP][1] = clip[ 7] - clip[ 5];
	planes[TOP][2] = clip[11] - clip[ 9];
	planes[TOP][3] = clip[15] - clip[13];
	normalizeFrustumPlane(TOP);

	planes[BACK][0] = clip[ 3] - clip[ 2];
	planes[BACK][1] = clip[ 7] - clip[ 6];
	planes[BACK][2] = clip[11] - clip[10];
	planes[BACK][3] = clip[15] - clip[14];
	normalizeFrustumPlane(BACK);

	planes[FRONT][0] = clip[ 3] + clip[ 2];
	planes[FRONT][1] = clip[ 7] + clip[ 6];
	planes[FRONT][2] = clip[11] + clip[10];
	planes[FRONT][3] = clip[15] + clip[14];
	normalizeFrustumPlane(FRONT);
	
}



