#ifndef _MESH_H_
#define _MESH_H_

#include "../math/algebra.h"

typedef struct {
	unsigned char v[3];
	unsigned char normalIndex;
}framePoint;

typedef struct {
	float scale[3];
	float translate[3];
	char name [16];
	framePoint fp[1];
} frame;

class mesh{
	
public:
	unsigned short 	meshIndex[3];
	unsigned short texIndex[3];
	
};

class model{
	
public:

	int numVertices;
	int numFaces;
	int numTexCoords;
	
	mesh *triIndex;
	vec2 *texCoordsList;
	vec3 *vertexList;
	
	//keyframe animation info
	int numFrames;
	int frameSize;
	int currentFrame;
	int nextFrame;
	float interpol;
	
};

#endif //_MESH_H_
