#ifndef MESHMANAGER_H_
#define MESHMANAGER_H_

#include <map>
#include <string>
#include "../../util/patterns/singleton.h"
#include "meshData.h"


/* TODO fazer o metodo free() que libera so um mesh X
 */

class MeshManager{
private:

	std::map<std::string, MeshData*> ids;
	
public:

 	MeshManager() { };
	~MeshManager() {};
	MeshData* load(char *name );
	void free(char *name);
	void freeAll();
};

typedef singleton<MeshManager> MESHMANAGER;


#endif /*MESHMANAGER_H_*/
