
#include "objData.h"
#include "objload.h"

ObjData::ObjData(){

	nverts = 0;
	nindices = 0;
	indices = NULL;
	vertexdata = NULL;
	normaldata = NULL;
	tangentdata = NULL;
	binormaldata = NULL;
	texcoords = NULL;
	
}

ObjData::~ObjData(){

	if (indices)
		delete indices;
	if (vertexdata)
		delete vertexdata;
	if (normaldata)
		delete normaldata;
	if (tangentdata)
		delete tangentdata;
	if (binormaldata)
		delete binormaldata;
	if (texcoords)
		delete texcoords;
}

ObjData::ObjData(const char* filename){
	nverts = 0;
	nindices = 0;
	indices = NULL;
	vertexdata = NULL;
	normaldata = NULL;
	tangentdata = NULL;
	binormaldata = NULL;
	texcoords = NULL;
	load(filename);
}

bool ObjData::load(const char* fileName){
	return LoadObjModel( fileName, nverts, nindices, indices, vertexdata, normaldata, tangentdata, binormaldata, texcoords );
	
}

//TODO
void ObjData::unload(){
}
