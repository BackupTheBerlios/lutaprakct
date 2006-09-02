#ifndef MESHDATA_H_
#define MESHDATA_H_

#include <string>

/*essa classe ? so uma interface para todos os loaders de meshes*/

enum {
	UNKNOW  = 0,
	MD2MESH = 1,
	OBJMESH	= 2
};
	

class MeshData{
	
	public:
		
		MeshData(){};
		virtual ~MeshData(){};
		
		virtual bool load(const char* filename) = 0;
		virtual void unload() = 0;
		
		void setMeshType(int i){ meshType = i; };
		int getMeshType(){return meshType; };
		
	private:
		int meshType;
		
	
};

MeshData* loadMeshData(const char* filename);

#endif /*MESHDATA_H_*/
