#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <map>
#include <string>
#include "../../util/patterns/singleton.h"
#include "texture.h"

/* essa classe faz uma associacao usando map entre o nome do file da textura
 * e a textura carregada na memoria, assim ele fica sempre com as texxturas 
 * na memoria e quando eh pedido para ser carregado uma nova, ele verfica
 * se ela ja nao esta na memoria, se tiver retorna a texture, se nao carrega
 * na memoria
 */

/* TODO fazer o metodo free() que libera so uma textura X
 */

class textureManager{
private:

	std::map<std::string, texture*> ids;
	
public:

 	textureManager() { };
	~textureManager() {};
	texture* load(char *name, int target, int flag );
	void free(char *name);
	void freeAll();
};

typedef singleton<textureManager> TextureManager;

#endif //_TEXTUREMANAGER_H_
