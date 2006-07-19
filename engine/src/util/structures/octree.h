#ifndef OCTREE_H_
#define OCTREE_H_

#include <iostream>
#include "../glhelper/vbo.h"

enum NODE_ID
{
   TOP_FRONT_LEFT = 0,
   TOP_FRONT_RIGHT,
   TOP_BACK_LEFT,
   TOP_BACK_RIGHT,
   BOTTOM_FRONT_LEFT,
   BOTTOM_FRONT_RIGHT,
   BOTTOM_BACK_LEFT,
   BOTTOM_BACK_RIGHT
};

class Octree{
	
	public:
		Octree();
		~Octree();

		bool initialize(float *vertexList, int numVerts, float *t1, float *t2,
                      int maxLevels, int maxTris);
		void shutdown();

		bool isLeafNode() { return isLeaf; }
		bool isVertices() { return (vertices != NULL); }

		float *getVertices() { return vertices; }
		float *getTexCoord1() { return texCoord1; }
		float *getTexCoord2() { return texCoord2; }
		int getNumTriangles() { return (int)(numPoints / 3); }
		float getBoundingBoxSize() { return bbSize; }

		void getBoundingBoxCenter(float &cx, float &cy, float &cz)
		{
			cx = bbCenter[0]; cy = bbCenter[1]; cz = bbCenter[2];
		}

		Octree **getSubNodes() { return subNodes; }

		Vbo vert;
		Vbo texcoord1;
		Vbo texcoord2;

	private:
   
		void calculateBoundingBox(float *vertexList, int numVerts);
		void createNode(float *vertexList, int numVerts, float *t1, float *t2,
                      float *bbCenter, float bbSize);
		void createLeafNode(float *vList, int numVerts, float *t1, float *t2,
                          bool *bArray, int numTriangles, float *bbCenter,
                          float bbSize, int nodeId);
		float *getNodeCenter(float *bbCenter, float bbSize, int nodeId);


		// Leaf means node has data, else its a node.
		bool isLeaf;

		// List of node's vertex points.
		float *vertices;
		int numPoints;

		// Lost of node's tex coords.
		float *texCoord1;
		float *texCoord2;

		// Node's bounding box data.
		float bbCenter[3];
		float bbSize;

		Octree *subNodes[8];
	
};

#endif /*OCTREE_H_*/
