#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <map>
#include <string>
#include "../../../util/patterns/singleton.h"
#include "../../../util/glhelper/texture.h"

/* essa classe faz uma associacao usando map entre o nome do file da textura
 * e a textura carregada na memoria, assim ele fica sempre com as texxturas 
 * na memoria e quando eh pedido para ser carregado uma nova, ele verfica
 * se ela ja nao esta na memoria, se tiver retorna a texture, se nao carrega
 * na memoria
 */

/* TODO fazer o metodo free() que libera so uma textura X
 */

class TextureManager{
private:

	std::map<std::string, Texture*> ids;
	int flags;
	
public:

 	TextureManager() { };
	~TextureManager() {};
	Texture* load(std::string& filename, int target, int format, int internalformat, int flag );
	void setDefaultFlags();//default flags for texture loading
	int getFlags(){return flags; };
	void free(char *name);
	void freeAll();
};

typedef Singleton<TextureManager> TEXTUREMANAGER;

#endif //_TEXTUREMANAGER_H_
