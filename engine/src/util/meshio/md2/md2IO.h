#ifndef _MD2IO_H_
#define _MD2IO_H_

#include "../../math/algebra.h"
#include "../nvMeshIO.h"
#include "../../../modules/material/textures/texture.h"
#include "../../../modules/material/textures/texturemanager.h"

#define MD2_OK         0x0
#define MD2_ERR_MEM    0x1
#define MD2_ERR_FILE   0x2
#define MD2_ERR_FORMAT 0x4
 
 
struct MD2Header{
	
	int id;         // File Type - Normally 'IPD2'
	int version;    
	int texWidth;   // Texture width
	int texHeight;  // Texture height 
	int frameSize;  // Size for frames in bytes
	int numberTextures;  // Number of textures
	int numberVertices;  // Number of vertices
	int numberTexCoords; // Number of UVs
	int numberTriangles; // Number of polys
	int numberGLCmd;     // Number of GL Commmands
	int numberFrames;    // Number of frames
	int texOffset;  // Offset to texture name(s)
	int uvOffset;   // Offset to UV data
	int faceOffset; // Offset to poly data
	int frameOffset;// Offset to first frame  
	int GLCmdOffset;// Offset to GL Cmds          
	int EOFOffset;  // Size of file
};
 
 
struct MD2FrameInfo{
	
	float Scale[3];
	float Translate[3];
	char Name[16];
};
 
struct MD2Face{
	
	short p1,p2,p3;
	short uv1,uv2,uv3;
};
 
struct MD2Vtx{
	unsigned char Vtx[3];
	unsigned char lNorm;
};
 
struct Mesh_Vtx{	
  float x,y,z;
};
 
struct Mesh_UV{
  float u,v;
};
 
struct MD2Frame{
  Mesh_Vtx *Vtx;
  Mesh_Vtx *Norm;
};
 
struct MD2TexCoord{
  short u,v;
};	 
 
class MD2Obj{
	
	public:
		MD2Obj();
		~MD2Obj();
		int Load(char* filename);
		int GetFrameCount();
		char* GetTexName();
		void SetTexture(GLuint TexNum);
		void Draw(int Frame);
 
	private:
		int nFrames,nTri,nVtx,nUV;
		MD2Face *Face;
		MD2Frame *frame;
		Mesh_UV *UV;
		char TexName[64];
		GLuint TexID;
 
		void CalcNormal(Mesh_Vtx v1,Mesh_Vtx v2,Mesh_Vtx v3,Mesh_Vtx* Result);
};

#endif //_MD2IO_H_
