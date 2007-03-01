
#include "meshData.h"
#include "../../util/meshio/md2/md2IO.h"
#include "../../util/meshio/obj/objData.h"

MeshData* loadMeshData(const char* filename){

	char* aux = strchr (filename, '.');
	aux++;
	MeshData *ret;
	if ((strcmp (aux, "md2") == 0) || (strcmp (aux, "MD2") == 0)){
        ret = new MD2Obj();
        ret->load(filename);
        ret->setMeshType(MD2MESH);
        return ret;
	}else if ((strcmp (aux, "obj") == 0) || (strcmp (aux, "OBJ") == 0)){
		ret = new ObjData();
        ret->load(filename);
        ret->setMeshType(OBJMESH);
        return ret;
	}
	return NULL;
	
}
