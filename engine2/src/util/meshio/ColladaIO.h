#ifndef COLLADAIO_H_
#define COLLADAIO_H_

/*essa classe le o formato collada. alguns dados do formato sao desprezados
 * como luzes e cameras, apenas a informacao geometrica e parte do material 
 * é lido. usa tinyxml como parser xml */

#include "../tinyxml/tinyxml.h"
#include <list>
#include <string>

class InstanceMaterial{
	
	public:
	
		InstanceMaterial(){};
		~InstanceMaterial(){};
		
		std::string symbol;
		std::string target;
		std::string semantic;
		std::string input_semantic;
	
};

class ColladaNode{

	public:
		ColladaNode(){};
		~ColladaNode(){};
		
		std::string geometryUrl;

		std::list<InstanceMaterial*> materials;
	
};

class ColladaMeshData{
	
	public:
	
		ColladaMeshData():indices(NULL), vertexdata(NULL), normaldata(NULL),
					tangentdata(NULL), binormaldata(NULL){
					nverts = 0;
					nindices = 0;
					ntextures = 0;};
					
		~ColladaMeshData(){
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
		
		unsigned int nverts;
		unsigned int nindices;
		unsigned int ntextures; 
		
		unsigned int *indices;
		float *vertexdata;
		float *normaldata;
		float *tangentdata;
		float *binormaldata;
		float *texcoords[8];
		
};
 
class ColladaIO{
	
	public: 
		ColladaIO(){};
		ColladaIO(char* filename){ load(filename); };
		~ColladaIO(){unload();};
		
		bool load(char* filename);
		void unload();

	
		std::list<ColladaMeshData* > meshes;
	
	private:
	
		void readIndices(TiXmlElement* tag, ColladaMeshData* mesh);
		void readVertices(TiXmlElement* tag,  ColladaMeshData* mesh, std::string source);
		void readNormals(TiXmlElement* tag,  ColladaMeshData* mesh, std::string source);
		void readTexcoords(TiXmlElement* tag,  ColladaMeshData* mesh, std::string source, int set);
		
		void readMaterial(TiXmlElement* tag, TiXmlElement* tag,  ColladaMeshData* mesh);
		void readGeometry(std::string url, TiXmlElement* tag);
		
		void readNodes(TiXmlElement* tag);
	
		unsigned int getNumberOfInputs(TiXmlElement* tag);
		unsigned int getNumberOfTextures(TiXmlElement* tag);
		unsigned int getVertexOffset(TiXmlElement* tag);
		
};

#endif /*COLLADAIO_H_*/
