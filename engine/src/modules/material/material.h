engi#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../textures/texture.h"
#include "../textures/texturemanager.h"

/* interface da classe responsavel pelo material. os outros tipos de material
 * devem herdar dessa classe e possuem informa?oes adicionais e metodos adicionais
 * por exemplo, um material de luz per pixel simples nao precisa de mais de uma textura
 * ja um material de normal map precisa de no minimo 2, etc
*/

#include <list>

class material {
	
public:

	material() {baseTex = NULL;};
	virtual ~material() { if (baseTextures) baseTextures.clear(); };
	
	void setEmissiveConstant(float ke) { kEmissive = ke; };
	void setAmbientConstant(float ka) { kAmbient = ka; };
	void setDiffuseConstant(float kd) { kDiffuse = kd; };
	void setSpecularConstant(float ks) { kSpecular = ks; };
	void setShininess(float s) {shininess = s; };
	
	void addBaseTexture(std::string filename, int flags){ 
		texture *t;
		t = TextureManager::getInstance().load(filename.c_str(), flags);   
		baseTextures.push_back(t);
	};
	
	virtual void initialize(std::string filename) = 0;
	virtual void bind() = 0;
	virtual void unbind() = 0;
	
protected:
	
	std::string name;
	std::string shadername;
	bool hasShader;
	
	float color[4];
	float secundaryColor[4];
	float shininess;
	float kEmissive, kAmbient, kDiffuse, kSpecular;

	std::list<texture *> baseTextures;
	
	
};

#endif //_MATERIAL_H_
