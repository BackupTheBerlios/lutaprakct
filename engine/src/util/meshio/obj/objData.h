#ifndef OBJDATA_H_
#define OBJDATA_H_

#include "../../../modules/mesh/meshData.h"

class ObjData : public MeshData {
	
	public:
	
		ObjData();
		ObjData(const char* filename);
		virtual ~ObjData();
		
		virtual bool load(const char* filename);
		virtual void unload();
	
		unsigned int nverts;
		unsigned int nindices;
		unsigned int *indices;
		float *vertexdata;
		float *normaldata;
		float *tangentdata;
		float *binormaldata;
		float *texcoords;
		
	
};	


#endif /*OBJDATA_H_*/
