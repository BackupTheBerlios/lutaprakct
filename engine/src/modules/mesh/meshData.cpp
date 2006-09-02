
#include "meshData.h"
#include "../../util/meshio/md2/md2IO.h"

MeshData* loadMeshData(const char* filename){

	char* aux = strchr (filename, '.');
	aux++;
	MeshData *ret;
	if ((strcmp (aux, "md2") == 0) || (strcmp (aux, "MD2") == 0)){
        ret = new MD2Obj();
        ret->load(filename);
        ret->setMeshType(MD2MESH);
        return ret;
	}
	return NULL;
	
}
