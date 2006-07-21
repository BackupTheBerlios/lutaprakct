
#include "octree.h"

int g_currentLevel = 0;
int g_maxLevel = 0;
int g_maxTriangles = 0;

Octree::Octree() : isLeaf(0), vertices(0), numPoints(0), texCoord1(0),
                     texCoord2(0), bbSize(0){
                     	
	bbCenter[0] = bbCenter[1] = bbCenter[2] = 0;
	for(int i = 0; i < 8; i++) 
		subNodes[i] = NULL;
}


Octree::~Octree(){
   shutdown();
}


bool Octree::initialize(float *vertexList, int numVerts, float *t1, float *t2,
                         int maxLevels, int maxTris){
	g_maxLevel = maxLevels;
	g_maxTriangles = maxTris;
	numPoints = numVerts;

   // Calculate the bounding box then recursively create
   // all child nodes.
	calculateBoundingBox(vertexList, numVerts);
	createNode(vertexList, numVerts, t1, t2, bbCenter, bbSize);
	return true;
}


void Octree::calculateBoundingBox(float *vertexList, int numVerts){
	
	float maxWidth = 0, maxHeight = 0, maxDepth = 0;

	if(vertexList == NULL || numVerts <= 0) 
		return;

	bbCenter[0] = bbCenter[1] = bbCenter[2] = 0;

   // soma todos os vertices
	for(int i = 0; i < numVerts * 3; i+= 3 ){
		bbCenter[0] = bbCenter[0] + vertexList[i];
		bbCenter[1] = bbCenter[1] + vertexList[i + 1];
		bbCenter[2] = bbCenter[2] + vertexList[i + 2];
	}

   // divide pelo numero de vertices para pegar o centro
	bbCenter[0] /= numVerts;
	bbCenter[1] /= numVerts;
	bbCenter[2] /= numVerts;

   // Loop em todos os vertices para pegar o mais distante
   //do centro
	for(int i = 0; i < numVerts * 3; i += 3){
         // Get the distance of this vertex to the center.
		float width = vertexList[i + 0] - bbCenter[0];
		float height = vertexList[i + 1] - bbCenter[1];
		float depth = vertexList[i + 2] - bbCenter[2];

         // Make sure they are not negative numbers.
		if(width < 0) 
			width *= -1;
		if(height < 0) 
			height *= -1;
		if(depth < 0) 
			depth *= -1;

         // Update if any of these are bigger than the recorded max.
		if(width > maxWidth) 
			maxWidth = width;
		if(height > maxHeight) 
			maxHeight = height;
		if(depth > maxDepth) 
			maxDepth = depth;
	}

   // Convert from radius distance to diameter of each axis.
   maxWidth *= 2;
   maxHeight *= 2;
   maxDepth *= 2;

   // pega a maior distancia e coloca
   // como tamanho do bounding box
   bbSize = maxWidth;
   if(bbSize < maxHeight)
		bbSize = maxHeight;
   if(bbSize < maxDepth) 
		bbSize = maxDepth;
}


void Octree::createNode(float *vertexList, int numVerts, float *t1, float *t2,
                         float *bbCenter, float bbSize){
                         	
	int numTriangles = numVerts / 3;
	this->bbSize = bbSize;

	this->bbCenter[0] = bbCenter[0];
	this->bbCenter[1] = bbCenter[1];
	this->bbCenter[2] = bbCenter[2];

	//quando chega no limite aceitavel de triangulos ou de nivel maximo
	//da arvore. salva as informa?oes nesse no. se nao cria os nos filhos
	//e continua descendo a arvore
	if(numTriangles <= g_maxTriangles || g_currentLevel >= g_maxLevel){
		isLeaf = true;
		numPoints = numVerts;
		vertices = new float[numVerts * 3];
		texCoord1 = new float[numVerts * 2];
		texCoord2 = new float[numVerts * 2];
		memcpy(vertices, vertexList, sizeof(float) * numVerts * 3);
		memcpy(texCoord1, t1, sizeof(float) * numVerts * 2);
		memcpy(texCoord2, t2, sizeof(float) * numVerts * 2);

		vert.initialize(ARRAY, sizeof(float) * numVerts * 3, (void*) vertices, STATIC_DRAW);
		texcoord1.initialize(ARRAY, sizeof(float) * numVerts * 2, (void*) texCoord1, STATIC_DRAW);
		texcoord2.initialize(ARRAY, sizeof(float) * numVerts * 2, (void*) texCoord2, STATIC_DRAW);
		vert.unbind();

		delete []vertices;
		delete []texCoord1;
		delete []texCoord2;		
	}else{
		isLeaf = false;

		int size1 = 0; int size2 = 0; int size3 = 0; int size4 = 0;
		int size5 = 0; int size6 = 0; int size7 = 0; int size8 = 0;
		bool *bArray1 = new bool[numTriangles];
		bool *bArray2 = new bool[numTriangles];
		bool *bArray3 = new bool[numTriangles];
		bool *bArray4 = new bool[numTriangles];
		bool *bArray5 = new bool[numTriangles];
		bool *bArray6 = new bool[numTriangles];
		bool *bArray7 = new bool[numTriangles];
		bool *bArray8 = new bool[numTriangles];
		memset(bArray1, 0, numTriangles);
		memset(bArray2, 0, numTriangles);
		memset(bArray3, 0, numTriangles);
		memset(bArray4, 0, numTriangles);
		memset(bArray5, 0, numTriangles);
		memset(bArray6, 0, numTriangles);
		memset(bArray7, 0, numTriangles);
		memset(bArray8, 0, numTriangles);

		int t = 0;

		//loop em todos os triangulos pra determinar em qual dos 8 nos eles entram
		for(int i = 0; i < numVerts * 3; i+=3 ){
               // Top left front check.
			if((vertexList[i + 0] <= bbCenter[0]) && (vertexList[i + 1] >= bbCenter[1]) &&
			  (vertexList[i + 2] >= bbCenter[2])) { 
				bArray1[t / 3] = true; 
			}

               // Top right front check.
			if((vertexList[i + 0] >= bbCenter[0]) && (vertexList[i + 1] >= bbCenter[1]) &&
              (vertexList[i + 2] >= bbCenter[2])) { 
				bArray2[t / 3] = true; 
			}

               // Top left back check.
			if((vertexList[i + 0] <= bbCenter[0]) && (vertexList[i + 1] >= bbCenter[1]) &&
			  (vertexList[i + 2] <= bbCenter[2])) { 
				bArray3[t / 3] = true; 
			}

               // Top right back check.
			if((vertexList[i + 0] >= bbCenter[0]) && (vertexList[i + 1] >= bbCenter[1]) &&
			  (vertexList[i + 2] <= bbCenter[2])) { 
				bArray4[t / 3] = true; 
			}

               // Bottom left front check.
			if((vertexList[i + 0] <= bbCenter[0]) && (vertexList[i + 1] <= bbCenter[1]) &&
			  (vertexList[i + 2] >= bbCenter[2])) { 
				bArray5[t / 3] = true; 
			}

               // Bottom right front check.
			if((vertexList[i + 0] >= bbCenter[0]) && (vertexList[i + 1] <= bbCenter[1]) &&
			  (vertexList[i + 2] >= bbCenter[2])) { 
				bArray6[t / 3] = true; 
			}

               // Bottom left back check.
			if((vertexList[i + 0] <= bbCenter[0]) && (vertexList[i + 1] <= bbCenter[1]) &&
			  (vertexList[i + 2] <= bbCenter[2])) { 
				bArray7[t / 3] = true; 
			}

               // Bottom right back check.
			if((vertexList[i + 0] >= bbCenter[0]) && (vertexList[i + 1] <= bbCenter[1]) &&
			  (vertexList[i + 2] <= bbCenter[2])) { 
				bArray8[t / 3] = true; 
			}

			t++;
		}

         // Quantos triangulos em cada no.
		for(int i = 0; i < numTriangles; i++){
			if(bArray1[i] == true) 
				size1++;
			if(bArray2[i] == true) 
				size2++;
			if(bArray3[i] == true) 
				size3++;
			if(bArray4[i] == true) 
				size4++;
			if(bArray5[i] == true) 
				size5++;
			if(bArray6[i] == true) 
				size6++;
			if(bArray7[i] == true) 
				size7++;
			if(bArray8[i] == true) 
				size8++;
		}

         // Create each sub node.
		createLeafNode(vertexList, numVerts, t1, t2, bArray1, size1, bbCenter, bbSize, TOP_FRONT_LEFT);
		createLeafNode(vertexList, numVerts, t1, t2, bArray2, size2, bbCenter, bbSize, TOP_FRONT_RIGHT);
		createLeafNode(vertexList, numVerts, t1, t2, bArray3, size3, bbCenter, bbSize, TOP_BACK_LEFT);
		createLeafNode(vertexList, numVerts, t1, t2, bArray4, size4, bbCenter, bbSize, TOP_BACK_RIGHT);
		createLeafNode(vertexList, numVerts, t1, t2, bArray5, size5, bbCenter, bbSize, BOTTOM_FRONT_LEFT);
		createLeafNode(vertexList, numVerts, t1, t2, bArray6, size6, bbCenter, bbSize, BOTTOM_FRONT_RIGHT);
		createLeafNode(vertexList, numVerts, t1, t2, bArray7, size7, bbCenter, bbSize, BOTTOM_BACK_LEFT);
		createLeafNode(vertexList, numVerts, t1, t2, bArray8, size8, bbCenter, bbSize, BOTTOM_BACK_RIGHT);

         // Free temp data.
		delete[] bArray1;
		delete[] bArray2;
		delete[] bArray3;
		delete[] bArray4;
		delete[] bArray5;
		delete[] bArray6;
		delete[] bArray7;
		delete[] bArray8;
	}
}


void Octree::createLeafNode(float *vList, int numVerts, float *t1, float *t2,
                             bool *bArray, int numTriangles, float *bbCenter,
                             float bbSize, int nodeId){
                             	
	float *vertexList = NULL, *texCoord1 = NULL, *texCoord2 = NULL;
	int vCount = 0;
	int t1Count = 0, t2Count = 0;

	//se nao tiver um dos parametros.
	if(!vList || !bArray || !bbCenter || numTriangles <= 0 || numVerts <= 0 || !t1 || !t2) 
			return;

   // aloca a memoria.
	vertexList = new float[(numTriangles * 3) * 3];
	texCoord1 = new float[(numTriangles * 3) * 2];
	texCoord2 = new float[(numTriangles * 3) * 2];

	int t = 0;

   // Loop through and copy all vertices that fall within
   // this node in the temp buffers.
	for(int i = 0, i2 = 0; i < numVerts * 3; i+=3, i2+=2){
		if(bArray[t / 3]){
			vertexList[vCount++] = vList[i + 0];
			vertexList[vCount++] = vList[i + 1];
			vertexList[vCount++] = vList[i + 2];
               
			texCoord1[t1Count++] = t1[i2 + 0];
			texCoord1[t1Count++] = t1[i2 + 1];

			texCoord2[t2Count++] = t2[i2 + 0];
			texCoord2[t2Count++] = t2[i2 + 1];
		}

		t++;
	}

   // Allocate this sub node.
	subNodes[nodeId] = new Octree();

   // Get the center of this node's bounding box.
	float *pC = getNodeCenter(bbCenter, bbSize, nodeId);
	float center[3];
	center[0] = pC[0]; center[1] = pC[1]; center[2] = pC[2];

	g_currentLevel++;

   // Recursively keep doing down the tree.
	subNodes[nodeId]->createNode(vertexList, numTriangles * 3, texCoord1,
                                  texCoord2, center, bbSize / 2);

	g_currentLevel--;

   // Delete temp buffers.
	delete[] vertexList;
	delete[] texCoord1;
	delete[] texCoord2;
}


float *Octree::getNodeCenter(float *bbCenter, float bbSize, int nodeId){
	
	float newCenter[3];
	newCenter[0] = newCenter[1] = newCenter[2] = 0;

   // Depending on which node we are dealing with
   // will depend on how we calculate the center.
	switch(nodeId){
		
		case TOP_FRONT_LEFT:
				newCenter[0] = bbCenter[0] - bbSize / 4;
				newCenter[1] = bbCenter[1] + bbSize / 4;
				newCenter[2] = bbCenter[2] + bbSize / 4;
				break;

		case TOP_FRONT_RIGHT:
				newCenter[0] = bbCenter[0] + bbSize / 4;
				newCenter[1] = bbCenter[1] + bbSize / 4;
				newCenter[2] = bbCenter[2] + bbSize / 4;
				break;

		case TOP_BACK_LEFT:
				newCenter[0] = bbCenter[0] - bbSize / 4;
				newCenter[1] = bbCenter[1] + bbSize / 4;
				newCenter[2] = bbCenter[2] - bbSize / 4;
				break;

		case TOP_BACK_RIGHT:
				newCenter[0] = bbCenter[0] + bbSize / 4;
				newCenter[1] = bbCenter[1] + bbSize / 4;
				newCenter[2] = bbCenter[2] - bbSize / 4;
				break;

		case BOTTOM_FRONT_LEFT:
				newCenter[0] = bbCenter[0] - bbSize / 4;
				newCenter[1] = bbCenter[1] - bbSize / 4;
				newCenter[2] = bbCenter[2] + bbSize / 4;
				break;

		case BOTTOM_FRONT_RIGHT:
				newCenter[0] = bbCenter[0] + bbSize / 4;
				newCenter[1] = bbCenter[1] - bbSize / 4;
				newCenter[2] = bbCenter[2] + bbSize / 4;
				break;

		case BOTTOM_BACK_LEFT:
				newCenter[0] = bbCenter[0] - bbSize / 4;
				newCenter[1] = bbCenter[1] - bbSize / 4;
				newCenter[2] = bbCenter[2] - bbSize / 4;
				break;

		case BOTTOM_BACK_RIGHT:
				newCenter[0] = bbCenter[0] + bbSize / 4;
				newCenter[1] = bbCenter[1] - bbSize / 4;
				newCenter[2] = bbCenter[2] - bbSize / 4;
				break;
	}

	return &newCenter[0];
}



void Octree::shutdown(){
	
   // Release all data.

	numPoints = 0;
	isLeaf = false;

	if(vertices != NULL){
			delete[] vertices;
			vertices = NULL;
	}

	if(texCoord1 != NULL){
		delete[] texCoord1;
		texCoord1 = NULL;
	}

	if(texCoord2 != NULL){
		delete[] texCoord2;
		texCoord2 = NULL;
	}

	for(int i = 0; i < 8; i++){
		if(subNodes[i] != NULL){
			subNodes[i]->shutdown();
			delete subNodes[i];
			subNodes[i] = NULL;
		}
	}
}
