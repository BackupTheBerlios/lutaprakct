#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../textures/texture.h"

/* classe totalmente experimental ainda
*/

class material {
public:

	std::string name;
	float color[4];
	float secundaryColor[4];
	float power;
	float specularColor[4], emissiveColor[4];

	texture *tex;
};

#endif //_MATERIAL_H_
