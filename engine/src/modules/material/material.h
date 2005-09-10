#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../textures/texture.h"

/* classe totalmente experimental ainda
 * eh apenas um esbo?o, ainda vai mudar muito */

class material {
public:

	bool isName(std::string &text){if (strcmp(text.c_str(), name.c_str()) == 0) return true; return false;};
	std::string name;
	float faceColor[4];
	float power;
	float specularColor[4], emissiveColor[4];

	texture *tex;
};

#endif //_MATERIAL_H_
