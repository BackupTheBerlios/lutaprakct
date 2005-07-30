#ifndef _SPRITEMANAGER_H_
#define _SPRITEMANAGER_H_

#include "spritebase.h"
#include "../../util/singleton.h"
#include <string>
#include <map>

/** spriteBase eh a imagem, sprite aponta para um spriteBase, dessa forma varios sprites podem
 * usar um mesmo spriteBase , economizando espaço na memoria, e para facilitar o uso dos
 * spritebase, essa classe eh responsável por carregar e manter eles na memoria.
 */

class spriteManager{
	
public:

	spriteBase* load(std::string filename);
	
	void free(std::string name);
	void freeAll();
	
private:
	
	std::map<std::string, spriteBase*> baseSprites;
	
};

typedef singleton<spriteManager> SpriteManager;

#endif //_SPRITEMANAGER_H_
