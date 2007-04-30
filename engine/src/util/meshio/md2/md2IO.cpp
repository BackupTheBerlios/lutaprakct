#include <math.h>
#include <GL/gl.h>
#include <cstdio>
#include <iostream>
#include <fstream>

#include "md2IO.h"

using namespace std;

MD2Obj::MD2Obj(){
	face = NULL;
	frame = NULL;
	texcoords = NULL;
 
	texID=0;
}
 
 
MD2Obj::~MD2Obj(){
	if(face){
		delete []face;
		face = NULL;
	}
 
	if(frame){
		delete []frame;
		frame = NULL;
	}
 
	if(texcoords){
		delete []texcoords;
		texcoords = NULL;
	}
}
 
 
bool MD2Obj::load(const char *filename){
	
	ifstream fIn;
	unsigned long fSize;
	unsigned char *data = NULL;
  
	MD2Header Head;
	long FrameLoop,ItemLoop;
	MD2Vtx *vtx;
	MD2TexCoord *MD2_UV;
	MD2FrameInfo FrameInfo;
 
  //deleta os dados se existirem
	if(face){
		delete []face;
		face = NULL;
	}
	if(frame){
		delete []frame;
		frame = NULL;
	}
	if(texcoords){
		delete []texcoords;
		texcoords = NULL;
	}
 
 
  // abre o arquivo
	fIn.open(filename, ios::binary);
    
	if(fIn==NULL)
		return false;
 
  // pega o tamanho do arquivo
	fIn.seekg(0,ios_base::end);
	fSize = fIn.tellg();
	fIn.seekg(0,ios_base::beg);
  // aloca o espa?o
	data = new unsigned char[fSize];
	if(data == NULL){
		fIn.close();
		return false;
	}
  // joga o arquivo na memoria e fecha o arquivo
	fIn.read((char*)data,fSize);
	fIn.close();
 
 
  // copia os primeiros 68 bytes onde esta o header
	memcpy(&Head, data, 68);
 

/*	cout<<"ID - "<<data[0]<<data[1]<<data[2]<<data[3]<<"\n";
	cout<<"Version - "<<Head.version<<"\n";   
	cout<<"Tex Width - "<<Head.texWidth<<"\n";
	cout<<"Tex Height - "<<Head.texHeight<<"\n";
	cout<<"Frame Size - "<<Head.frameSize<<"\n";
	cout<<"Textures - "<<Head.numberTextures<<"\n";
	cout<<"Vertices - "<<Head.numberVertices<<"\n";
	cout<<"UVs - "<<Head.numberTexCoords<<"\n";
	cout<<"Faces - "<<Head.numberTriangles<<"\n";
	cout<<"GL cmds - "<<Head.numberGLCmd<<"\n";
	cout<<"Frames - "<<Head.numberFrames<<"\n";
	cout<<"Skin Offset - "<<Head.texOffset<<"\n";
	cout<<"UV Offset - "<<Head.uvOffset<<"\n";
	cout<<"Face Offset - "<<Head.faceOffset<<"\n";
	cout<<"Frame Offset - "<<Head.frameOffset<<"\n";
	cout<<"GL Offset - "<<Head.GLCmdOffset<<"\n";
	cout<<"Filesize - "<<Head.EOFOffset<<"\n";
 */
 
  //testa se ? um md2
	if(Head.id != 844121161) 
		return false;
 
	if(Head.version != 8)
		return false;
 
	if(Head.EOFOffset != fSize)
		return false;
 
 
  // pega agluma info sobre a quantidade de vertices, etc
	totalFrames = Head.numberFrames;
	totalTri = Head.numberTriangles;
	totalVertices = Head.numberVertices;
	totalTexcoords = Head.numberTexCoords;
 
  // aloca a memoria
 
  // Frames
	frame = new MD2Frame[totalFrames];
 
	if(!frame){
		delete []data;
		return false;
	}
 
  // Frame components
	for(FrameLoop = 0; FrameLoop != totalFrames; ++FrameLoop){
		
		frame[FrameLoop].Vtx = new Mesh_Vtx[totalVertices];
		frame[FrameLoop].Norm= new Mesh_Vtx[totalVertices];
 
		if(!frame[FrameLoop].Vtx || !frame[FrameLoop].Norm){
			delete []data;
			return false;
		}
	}
 
  // MD2 vtx buffer
	vtx = new MD2Vtx[Head.numberVertices];
  // Faces
	face = new MD2Face[Head.numberTriangles];
  // UVs
	texcoords = new Mesh_UV[totalTexcoords];
  // MD2 UV buffer
	MD2_UV = new MD2TexCoord[Head.numberTexCoords];
 
 
  // verifica se as arrays estao ok
	if(!vtx || !face || !texcoords || !MD2_UV){
		delete []data;
		return false;
	}
 
 
  
  // le o nome da textura
	if(Head.numberTextures>0){
		memcpy(texName, &data[Head.texOffset], 64);
	}
 
  // le as faces
	memcpy(face, &data[Head.faceOffset], Head.numberTriangles*sizeof(MD2Face));
 
  // le as uvs
	memcpy(MD2_UV,&data[Head.uvOffset],Head.numberTexCoords*sizeof(MD2TexCoord));
 
	for(ItemLoop = 0; ItemLoop != totalTexcoords; ++ItemLoop){
		texcoords[ItemLoop].u = ((float)MD2_UV[ItemLoop].u)/Head.texWidth;
		texcoords[ItemLoop].v = ((float)MD2_UV[ItemLoop].v)/Head.texHeight;
	}
	delete []MD2_UV;

  // le os vertices
	for(FrameLoop=0; FrameLoop != totalFrames; ++FrameLoop){
		memcpy(&FrameInfo, &data[Head.frameOffset + (Head.frameSize * FrameLoop)],sizeof(FrameInfo)); 
		memcpy(vtx, &data[Head.frameOffset + (Head.frameSize * FrameLoop) + sizeof(FrameInfo)], totalVertices * sizeof(MD2Vtx));
		for(ItemLoop=0; ItemLoop != totalVertices; ++ItemLoop){
			frame[FrameLoop].Vtx[ItemLoop].x=(vtx[ItemLoop].Vtx[0] * FrameInfo.Scale[0])+FrameInfo.Translate[0];
			frame[FrameLoop].Vtx[ItemLoop].y=(vtx[ItemLoop].Vtx[1] * FrameInfo.Scale[0])+FrameInfo.Translate[1];   
			frame[FrameLoop].Vtx[ItemLoop].z=(vtx[ItemLoop].Vtx[2] * FrameInfo.Scale[0])+FrameInfo.Translate[2];
		}
	}
 
	delete [] vtx;
	delete [] data;
 
 
  // calcula as normais em cada frame
/*	for(FrameLoop=0; FrameLoop != totalFrames; FrameLoop++){
		for(ItemLoop = 0; ItemLoop != totalTri; ItemLoop++){
			calcNormal(frame[FrameLoop].Vtx[face[ItemLoop].p1],
                   frame[FrameLoop].Vtx[face[ItemLoop].p2],
                   frame[FrameLoop].Vtx[face[ItemLoop].p3],
                   &frame[FrameLoop].Norm[ItemLoop]);
 
		}
	}*/
	return true;
 }
 
 
int MD2Obj::getFrameCount(){
  return totalFrames;
}
 
 
char* MD2Obj::getTexName(){
   if(texName)
    return texName;
   else
    return NULL;
}
 
 
void MD2Obj::setTexture(GLuint TexNum){
  texID = TexNum;
}
 
 
void MD2Obj::draw(int Frame){
	
	int Part;
 
	if(Frame >= totalFrames)
		Frame=0;
 
	glBegin(GL_TRIANGLES);  
 
	for(Part=0; Part < totalTri; ++Part){
		glNormal3f(frame[Frame].Norm[Part].x, frame[Frame].Norm[Part].y, frame[Frame].Norm[Part].z);
	
		glTexCoord2f(texcoords[face[Part].uv1].u, texcoords[face[Part].uv1].v);
		glVertex3f(frame[Frame].Vtx[face[Part].p1].x, frame[Frame].Vtx[face[Part].p1].y, frame[Frame].Vtx[face[Part].p1].z);
	
		glTexCoord2f(texcoords[face[Part].uv2].u, texcoords[face[Part].uv2].v);
		glVertex3f(frame[Frame].Vtx[face[Part].p2].x, frame[Frame].Vtx[face[Part].p2].y, frame[Frame].Vtx[face[Part].p2].z);
	
		glTexCoord2f(texcoords[face[Part].uv3].u, texcoords[face[Part].uv3].v);
		glVertex3f(frame[Frame].Vtx[face[Part].p3].x, frame[Frame].Vtx[face[Part].p3].y, frame[Frame].Vtx[face[Part].p3].z);
	}  
 
	glEnd();
 
}
 
 
void MD2Obj::calcNormal(Mesh_Vtx v1,Mesh_Vtx v2,Mesh_Vtx v3,Mesh_Vtx* Result){
	double v1x,v1y,v1z,v2x,v2y,v2z;
	double nx,ny,nz;
	double vLen;
 
  // Calculate vectors
	v1x = v1.x - v2.x;
	v1y = v1.y - v2.y;
	v1z = v1.z - v2.z;
 
	v2x = v2.x - v3.x;
	v2y = v2.y - v3.y;
	v2z = v2.z - v3.z;
  
  // Get cross product of vectors
 
	nx = (v1y * v2z) - (v1z * v2y);
	ny = (v1z * v2x) - (v1x * v2z);
	nz = (v1x * v2y) - (v1y * v2x);
 
  // Normalise final vector
	vLen = sqrt( (nx * nx) + (ny * ny) + (nz * nz) );
 
	Result->x = (float) (nx / vLen);
	Result->y = (float) (ny / vLen);
	Result->z = (float) (nz / vLen);
}
