#include "md2IO.h"
#include <math.h>
#include <GL/gl.h>
#include <cstdio>
#include <iostream>

// CalculateNormal()
// desc: given 3 points, calculates the normal to the points
void CalculateNormal( vec3 p1, vec3 p2, vec3 p3 )
{
   float a[3], b[3], result[3];
   float length;

   a[0] = p1.x - p2.x;
   a[1] = p1.y - p2.y;
   a[2] = p1.z - p2.z;

   b[0] = p1.x - p3.x;
   b[1] = p1.y - p3.y;
   b[2] = p1.z - p3.z;

   result[0] = a[1] * b[2] - b[1] * a[2];
   result[1] = b[0] * a[2] - a[0] * b[2];
   result[2] = a[0] * b[1] - b[0] * a[1];

   // calculate the length of the normal
   length = (float)sqrt(result[0]*result[0] + result[1]*result[1] + result[2]*result[2]);

   // normalize and specify the normal
   glNormal3f(result[0]/length, result[1]/length, result[2]/length);
}

// CMD2Model constructor
md2IO::md2IO()
{
     numVertices = 0;    // vertices
     numTriangles = 0;   // triangles
     numFrames = 0;      // frames
     numST = 0;          // texture coordinates
     frameSize = 0;      // needed?
     currentFrame = 0;   // current keyframe 
     nextFrame = 1;      // next keyframe
     interpol = 0.0;     // interpolation percent
     triIndex = NULL;    // triangle indices
     st = NULL;          // texture coordinate indices
     vertexList = NULL;  // vertices
//  modelTex = TextureManager::getInstance.load( ;    // skin/texture
  
	fileExtensions.clear();
	fileExtensions.push_back("md2");
	fileExtensions.push_back("MD2");	  
  
}    

// CMD2Model destructor
md2IO::~md2IO()
{
	Unload();
}

const std::vector<const char*>& md2IO::GetFileExtensions() const 
{
	return fileExtensions;
}

// CMD2Model::SetupSkin()
// access: private
// desc: sets up the model skin/texture for OpenGL
/*void md2IO::SetupSkin()
{
     // set the proper parameters for an MD2 texture
     glGenTextures(1, &thisTexture->texID);
     glBindTexture(GL_TEXTURE_2D, thisTexture->texID);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_NEAREST);
     
     switch (thisTexture->textureType)
     {
     case BMP:
          gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, thisTexture->width, thisTexture->height, 
               GL_RGB, GL_UNSIGNED_BYTE, thisTexture->data);
          break;
     case PCX:
          gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, thisTexture->width, thisTexture->height,
               GL_RGBA, GL_UNSIGNED_BYTE, thisTexture->data);
		break;
     case TGA:
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, thisTexture->width, thisTexture->height,
			GL_RGB, GL_UNSIGNED_BYTE, thisTexture->data);
          break;
     default:
          break;
     }
}*/

// CMD2Model::Load()
// access: public
// desc: loads model and skin
int md2IO::ReadFile(const char *modelFile)
{
     FILE *filePtr;                          // file pointer
     int fileLen;                            // length of model file
     char *buffer;                           // file buffer
     
     modelHeader_t *modelHeader;             // model header
     
     vec2 *stPtr;                       // texture data
     frame_t *frame;                              // frame data
     vec3 *vertexListPtr;                // index variable
     mesh_t *bufIndexPtr;          // index variables
     int i, j;                               // index variables
     
     // open the model file
     filePtr = fopen(modelFile, "rb");
     if (filePtr == NULL){
     	std::cout << "no such file" << std::endl;
          return 0;
     }
     // find length of file
     std::cout << "lendo arquivo" << std::endl;
     fseek(filePtr, 0, SEEK_END);
     fileLen = ftell(filePtr);
     fseek(filePtr, 0, SEEK_SET);
     
     // read entire file into buffer
     buffer = new char [fileLen+1];
     fread(buffer, sizeof(char), fileLen, filePtr);
     
     // extract model file header from buffer
     modelHeader = (modelHeader_t*)buffer;
     
     vertexList = new vec3 [modelHeader->numXYZ * modelHeader->numFrames];
     
     numVertices = modelHeader->numXYZ;
     numFrames = modelHeader->numFrames;
     frameSize = modelHeader->framesize;
     
     for (j = 0; j < numFrames; j++)
     {
          frame = (frame_t*)&buffer[modelHeader->offsetFrames + frameSize * j];
          
          vertexListPtr = (vec3*)&vertexList[numVertices * j];
          for (i = 0; i < numVertices; i++)
          {
               vertexListPtr[i].x = frame->scale[0] * frame->fp[i].v[0] + frame->translate[0];
               vertexListPtr[i].y = frame->scale[1] * frame->fp[i].v[1] + frame->translate[1];
               vertexListPtr[i].z = frame->scale[2] * frame->fp[i].v[2] + frame->translate[2];
          }
     }
     std::cout << "vertices carregados" << std::endl;
     modelTex = TextureManager::getInstance().load("ogro2.tga", texture::TEXTURE_2D, texture::CLAMP | texture::RGB | texture::LINEAR_MIPMAP_LINEAR);// = LoadTexture(skinFile);
     std::cout << "textura carregada" << modelTex->getWidth() << " "  << modelTex->getHeight() <<std::endl;
    /* if (modelTex != NULL)
          SetupSkin();
     else
          return false;
     */
     numST = modelHeader->numST;
     st = new vec2 [numST];
     std::cout << "num st" << numST;
     stPtr = (vec2*)&buffer[modelHeader->offsetST];
     for (i = 0; i < numST; i++)
     {
          st[i].x = (float)stPtr[i].x / (float)modelTex->getWidth();
          st[i].y = (float)stPtr[i].y / (float)modelTex->getHeight();
          std::cout << "texcoord " << i << " x: " << stPtr[i].x  << " y: " << stPtr[i].x  << std::endl;
     }
     
     std::cout << "textura carregada" << std::endl;
     
     numTriangles = modelHeader->numTris;
    triIndex = new mesh_t [numTriangles];
     
     // point to triangle indexes in buffer
     bufIndexPtr = (mesh_t*)&buffer[modelHeader->offsetTris];
     
     // create a mesh (triangle) list
     float vpos[3];
     for (j = 0; j < numFrames; j++)         
     {
          // for all triangles in each frame
          for(i = 0; i < numTriangles; i++)
          {
               triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
               triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
               triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
               triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
               triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
               triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
          }
     }
     
     // close file and free memory
     fclose(filePtr);
	delete buffer;
     
     currentFrame = 0;
     nextFrame = 1;
     interpol = 0.0;
     
     return 1;
}

size_t md2IO::GetNumTriangles(){
	return numTriangles;
}

void md2IO::GetTriangleIndices(std::vector<int>& triangleIndices)
{
	triangleIndices = this->triangleIndices;
}

// CMD2Model::LoadModel()
// access: public
// desc: loads model from file
int md2IO::LoadModel(char *modelFile)
{
     FILE *filePtr;                          // file pointer
     int fileLen;                            // length of model file
     char *buffer;                           // file buffer
     
     modelHeader_t *modelHeader;             // model header
     
     vec2 *stPtr;                       // texture data
     frame_t *frame;                              // frame data
     vec3 *vertexListPtr;                // index variable
     mesh_t *triIndex, *bufIndexPtr;         // index variables
     int i, j;                               // index variables
     
     // open the model file
     filePtr = fopen(modelFile, "rb");
     if (filePtr == NULL)
          return false;
     
     // find length of file
     fseek(filePtr, 0, SEEK_END);
     fileLen = ftell(filePtr);
     fseek(filePtr, 0, SEEK_SET);
     
     // read entire file into buffer
     buffer = new char [fileLen+1];
     fread(buffer, sizeof(char), fileLen, filePtr);
     
     // extract model file header from buffer
     modelHeader = (modelHeader_t*)buffer;
     
     // allocate vertex list
     vertexList = new vec3 [modelHeader->numXYZ * modelHeader->numFrames];
     
     numVertices = modelHeader->numXYZ;
     numFrames = modelHeader->numFrames;
     frameSize = modelHeader->framesize;
     
     for (j = 0; j < numFrames; j++)
     {
          frame = (frame_t*)&buffer[modelHeader->offsetFrames + frameSize * j];
          
          vertexListPtr = (vec3*)&vertexList[numVertices * j];
          for (i = 0; i < numVertices; i++)
          {
               vertexListPtr[i].x = frame->scale[0] * frame->fp[i].v[0] + frame->translate[0];
               vertexListPtr[i].y = frame->scale[1] * frame->fp[i].v[1] + frame->translate[1];
               vertexListPtr[i].z = frame->scale[2] * frame->fp[i].v[2] + frame->translate[2];
          }
     }
     
     numST = modelHeader->numST;
     
     st = new vec2 [numST];
     
     stPtr = (vec2*)&buffer[modelHeader->offsetST];
     for (i = 0; i < numST; i++)
     {
          st[i].x = 0.0;
          st[i].y = 0.0;
     }
     
     numTriangles = modelHeader->numTris;
     triIndex = new mesh_t [numTriangles];
     
     // point to triangle indexes in buffer
     bufIndexPtr = (mesh_t*)&buffer[modelHeader->offsetTris];
     
     // create a mesh (triangle) list
     for (j = 0; j < numFrames; j++)         
     {
          // for all triangles in each frame
          for(i = 0; i < numTriangles; i++)
          {
               triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
               triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
               triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
               triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
               triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
               triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
          }
     }
     
     // close file and free memory
     fclose(filePtr);
	delete buffer;
     
    // modelTex = NULL;
     currentFrame = 0;
     nextFrame = 1;
     interpol = 0.0;
     
     return 0;
}

// CMD2Model::LoadSkin()
// access: public
// desc: loads a skin for the model
int md2IO::LoadSkin(char *skinFile)
{
     int i;
     
    // modelTex->LoadTexture(skinFile);
     
     //if (modelTex != NULL)
     //     SetupSkin(modelTex);
    // else
    //     return -1;
     
    //// for (i = 0; i < numST; i++)
    // {
       //   st[i].s /= (float)modelTex->width;
      //   st[i].t /= (float)modelTex->height;
    // }
     
     return 0;
}

// CMD2Model::SetTexture()
// access: public
// desc: sets a new texture object 
/*int CMD2Model::SetTexture(CTexture *texture)
{
     int i;
     
     if (texture != NULL)
	{
		free(modelTex);
          modelTex = texture;
	}
     else
          return -1;
     
     SetupSkin(modelTex);
     
     for (i = 0; i < numST; i++)
     {
          st[i].s /= (float)modelTex->width;
          st[i].t /= (float)modelTex->height;
     }
     
     return 0;
}*/

// CMD2Model::Animate()
// access: public
// desc: animates the model between the keyframes startFrame and endFrame
int md2IO::AnimateModel(int startFrame, int endFrame, float percent)
{
     vec3 *vList;              // current frame vertices
     vec3 *nextVList;          // next frame vertices
     int i;                                  // index counter
     float x1, y1, z1;                  // current frame point values
     float x2, y2, z2;                  // next frame point values
     
     vec3 vertex[3]; 
     
     if ((startFrame > currentFrame))
          currentFrame = startFrame;
     
     if ((startFrame < 0) || (endFrame < 0))
          return -1;
     
     if ((startFrame >= numFrames) || (endFrame >= numFrames))
          return -1;
     
     if (interpol >= 1.0)
     {
          interpol = 0.0f;
          currentFrame++;
          if (currentFrame >= endFrame)
               currentFrame = startFrame;
          
          nextFrame = currentFrame + 1;
          
          if (nextFrame >= endFrame)
               nextFrame = startFrame;
          
     }
     
     vList = &vertexList[numVertices*currentFrame];
     nextVList = &vertexList[numVertices*nextFrame];
     
	glColor4f(1.0, 1.0, 1.0, 1.0);
	modelTex->enable();
	modelTex->bind();
     glBegin(GL_TRIANGLES);
     for (i = 0; i < numTriangles; i++)
     {
          // get first points of each frame
          x1 = vList[triIndex[i].meshIndex[0]].x;
          y1 = vList[triIndex[i].meshIndex[0]].y;
          z1 = vList[triIndex[i].meshIndex[0]].z;
          x2 = nextVList[triIndex[i].meshIndex[0]].x;
          y2 = nextVList[triIndex[i].meshIndex[0]].y;
          z2 = nextVList[triIndex[i].meshIndex[0]].z;
          
          // store first interpolated vertex of triangle
          vertex[0].x = x1 + interpol * (x2 - x1);
          vertex[0].y = y1 + interpol * (y2 - y1);
          vertex[0].z = z1 + interpol * (z2 - z1);
          
          // get second points of each frame
          x1 = vList[triIndex[i].meshIndex[2]].x;
          y1 = vList[triIndex[i].meshIndex[2]].y;
          z1 = vList[triIndex[i].meshIndex[2]].z;
          x2 = nextVList[triIndex[i].meshIndex[2]].x;
          y2 = nextVList[triIndex[i].meshIndex[2]].y;
          z2 = nextVList[triIndex[i].meshIndex[2]].z;
          
          // store second interpolated vertex of triangle
          vertex[2].x = x1 + interpol * (x2 - x1);
          vertex[2].y = y1 + interpol * (y2 - y1);
          vertex[2].z = z1 + interpol * (z2 - z1);   
          
          // get third points of each frame
          x1 = vList[triIndex[i].meshIndex[1]].x;
          y1 = vList[triIndex[i].meshIndex[1]].y;
          z1 = vList[triIndex[i].meshIndex[1]].z;
          x2 = nextVList[triIndex[i].meshIndex[1]].x;
          y2 = nextVList[triIndex[i].meshIndex[1]].y;
          z2 = nextVList[triIndex[i].meshIndex[1]].z;
          
          // store third interpolated vertex of triangle
          vertex[1].x = x1 + interpol * (x2 - x1);
          vertex[1].y = y1 + interpol * (y2 - y1);
          vertex[1].z = z1 + interpol * (z2 - z1);
          
          // calculate the normal of the triangle
          CalculateNormal(vertex[0], vertex[2], vertex[1]);
          
          // render properly textured triangle
          glTexCoord2f(st[triIndex[i].stIndex[0]].x,
               st[triIndex[i].stIndex[0]].y);
          glVertex3f(vertex[0].x, vertex[0].y, vertex[0].z);
          
          glTexCoord2f(st[triIndex[i].stIndex[2]].x ,
               st[triIndex[i].stIndex[2]].y);
          glVertex3f(vertex[2].x, vertex[2].y, vertex[2].z );
          
          glTexCoord2f(st[triIndex[i].stIndex[1]].x,
               st[triIndex[i].stIndex[1]].y);
          glVertex3f(vertex[1].x, vertex[2].y, vertex[2].z);
     }
     glEnd();
	modelTex->disable();

     interpol += percent;  // increase percentage of interpolation between frames
     
     return 0;
}

// RenderFrame()
// desc: renders a single key frame
int md2IO::RenderFrame(int keyFrame)
{
     vec3 *vList;
     int i;
     
     // create a pointer to the frame we want to show
     vList = &vertexList[numVertices * keyFrame];
     
	//if (modelTex != NULL)
		// set the texture
	//	glBindTexture(GL_TEXTURE_2D, modelTex->texID);
     
     // display the textured model with proper lighting normals
     modelTex->enable();
     modelTex->bind();
     glBegin(GL_TRIANGLES);
     for(i = 0; i < numTriangles; i++)
     {
          CalculateNormal(vList[triIndex[i].meshIndex[0]],
               vList[triIndex[i].meshIndex[2]],
               vList[triIndex[i].meshIndex[1]]);

		//if (modelTex != NULL)
			glTexCoord2f(st[triIndex[i].stIndex[0]].x,
				st[triIndex[i].stIndex[0]].y);

          glVertex3f(vList[triIndex[i].meshIndex[0]].x, vList[triIndex[i].meshIndex[0]].y, vList[triIndex[i].meshIndex[0]].z);
          
		//if (modelTex != NULL)
			glTexCoord2f(st[triIndex[i].stIndex[2]].x ,
				st[triIndex[i].stIndex[2]].y);

          glVertex3f(vList[triIndex[i].meshIndex[2]].x, vList[triIndex[i].meshIndex[2]].y, vList[triIndex[i].meshIndex[2]].z);
          
		//if (modelTex != NULL)
			glTexCoord2f(st[triIndex[i].stIndex[1]].x,
				st[triIndex[i].stIndex[1]].y);

          glVertex3f(vList[triIndex[i].meshIndex[1]].x, vList[triIndex[i].meshIndex[1]].y, vList[triIndex[i].meshIndex[1]].z);
     }
     glEnd();
     modelTex->disable();
     return 0;
}

// Unload()
// desc: unloads model data from memory
void md2IO::Unload()
{
     if (triIndex != NULL)
          delete [] triIndex;
     if (vertexList != NULL)
          delete [] vertexList;
     if (st != NULL)
          delete [] st; 

//	if (modelTex != NULL)
//		delete modelTex;
}

