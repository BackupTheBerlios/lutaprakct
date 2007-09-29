#ifndef DATAMANAGER_H_
#define DATAMANAGER_H_

#include <map>
#include <string>
#include "../util/patterns/Singleton.h"

enum{
	TextureData = 1,
	MeshData
};

/*alguns dados so precisam estar 1vez na memoria, como meshes e texturas,
 * essa classe guarda mantem isso. a struct DataReference conta quantas
 * vezes um dado foi lido e  deletado, so quando chegar a 0 ele eh liberado
 * da memoria */

struct DataReference{
	
	int counter;
	void* data;
	int type;
	
};

/* associa string do filename a ser lido com um ponteiro pro dado */

class DataManager{
	
	public:
		
		DataManager();
		~DataManager();
	
		void* loadImage(std::string, int target, int format, int internalformat, int flag);
		void* loadMesh(std::string, int type);
	
		bool unload(std::string filename);
		
		bool unloadAll();
	
	private:
	
		std::map<std::string, DataReference> data;
		
		int textureFlags;
};

typedef Singleton<DataManager> DATAMANAGER;

#endif /*DATAMANAGER_H_*/
