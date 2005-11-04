#ifndef _MD2IO_H_
#define _MD2IO_H_

#include "../../../modules/math/algebra.h"
#include "../nvMeshIO.h"
#include "../../../modules/textures/texture.h"
#include "../../../modules/textures/texturemanager.h"
#define MAX_FRAMES 512


void CalculateNormal( float *p1, float *p2, float *p3 );


// info for a single frame point
typedef struct
{
   unsigned char v[3];
   unsigned char normalIndex;	// not used
} framePoint_t;

// information for a single frame
typedef struct
{
   float scale[3];
   float translate[3];
   char name[16];
   framePoint_t fp[1];
} frame_t;

// data for a single triangle
typedef struct
{
   unsigned short meshIndex[3];		// vertex indices
   unsigned short stIndex[3];		// texture coordinate indices
} mesh_t;

typedef struct
{
   int ident;		 // identifies as MD2 file "IDP2"
   int version;	 // mine is 8
   int skinwidth;    // width of texture
   int skinheight;   // height of texture
   int framesize;    // number of bytes per frame
   int numSkins;     // number of textures
   int numXYZ;       // number of points
   int numST;        // number of texture
   int numTris;      // number of triangles
   int numGLcmds;
   int numFrames;    // total number of frames
   int offsetSkins;  // offset to skin names (64 bytes each)
   int offsetST;     // offset of texture s-t values
   int offsetTris;   // offset of triangle mesh
   int offsetFrames; // offset of frame data (points)
   int offsetGLcmds; // type of OpenGL commands to use
   int offsetEnd;    // end of file
} modelHeader_t;


class md2IO : public nvMeshIO
{
private:

     int numFrames;			// number of model frames
     int numVertices;         // number of vertices
     int numTriangles;        // number of triangles
     int numST;               // number of skins
     int frameSize;           // size of each frame in bytes
     mesh_t *triIndex;        // triangle list
     vec2 *st;          // texture coordinate list
     vec3 *vertexList;    // vertex list
     texture *modelTex;     // texture data

    // void SetupSkin(CTexture *thisTexture);

	std::vector<const char*> fileExtensions;
	std::vector<int> triangleIndices;

protected:
     int currentFrame;        // current frame # in animation
     int nextFrame;           // next frame # in animation

public:
     float interpol;          // percent through current frame

     md2IO();        
     virtual ~md2IO();
     
    virtual const std::vector<const char*>& GetFileExtensions() const;
	virtual int ReadFile(const char* fileName);
	virtual size_t GetNumTriangles();
	
	virtual void GetTriangleIndices(std::vector<int>& triIndices);
	
	/***** Mesh Per-Vertex Attributes *****/
	// Returns the list of attributes (as strings) that are provided in the current file. Returns 0
	// if it did not have a file to read.
	virtual int GetAttributes(std::vector<const char*>& attributes){return 0; } ;
	
	virtual int GetAttributesAndValues(std::vector<const char*>& attributesRead, 
		std::vector<std::vector<float> >& attributeValueArrays, std::vector<size_t>& attributeSizes,
		std::vector<size_t>& attributeCounts) {return 0;};

	virtual int GetAttributeValues(const char* attribute, std::vector<float>& attributeValues, 
		size_t& attributeSize, size_t& attributeCount){ return 0;};

	
	/***** Group Info *****/
	// Get group 'types', e.g. SMOOTHING_GROUP, TEXCOORD_GROUP, ...
	virtual void GetGroupTypes(std::vector<const char*>& groupTypes){return;};
	// Get the 'names' of groups for a given attribute:
	virtual int GetGroups(const char* groupType, std::vector<const char*>& groupNames) {return 0;};
	// Get Group Info for given attribute, groupName,On return,triangleIndices will return the set of triangles which 
	// form the group, attributePresent indicates whether attribute was actually present in the file (e.g. a file
	// could define texture coordinate groups but not provide the coordinates themselves), If attributePresent is true,
	// the vector triangleAttributeIndices will be filled with the indices for each triangle - these index into
	// the vector returned by GetAttributeValues(attribute) below.
	virtual int GetGroupInfo(const char* attribute, const char* groupName, 
		std::vector<int>& triangleIndices, bool& attributePresent,
		std::vector<int>& triangleAttributeIndices, std::vector<int>& indexedTriangles){return 0;};
     // load model and skin/texture at the same time
    // int Load(char *modelFile, char *skinFile);

     // load model only
     int LoadModel(char *modelFile);

     // load skin only
     int LoadSkin(char *skinFile);

     // set model's texture/skin
   //  int SetTexture(CTexture *texture);

     // render model with interpolation to get animation
     int AnimateModel(int startFrame, int endFrame, float percent);

     // render a single frame
     int RenderFrame(int keyFrame);

     // free memory of model
     void Unload();

};
#endif //_MD2IO_H_
