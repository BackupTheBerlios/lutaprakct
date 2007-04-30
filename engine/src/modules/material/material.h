#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "materialData.h"
#include "../../util/glhelper/texture.h"
#include "textures/texturemanager.h"

/* interface da classe responsavel pelo material. os outros tipos de material
 * devem herdar dessa classe e possuem informa?oes adicionais e metodos adicionais
 * por exemplo, um material de luz per pixel simples nao precisa de mais de uma textura
 * ja um material de normal map precisa de no minimo 2, etc
*/

#include <list>

class Material {
	
public:

	Material() : materialConfig(NULL) { materialConfig = new MaterialData; };
	virtual ~Material() { if (!baseTextures.empty()) baseTextures.clear(); };
	
	void setEmissiveConstant(float *ke) { materialConfig->kEmissive[0] = ke[0]; materialConfig->kEmissive[1] = ke[1]; materialConfig->kEmissive[2] = ke[2];  };
	void setAmbientConstant(float *ka) { materialConfig->kAmbient[0] = ka[0]; materialConfig->kAmbient[1] = ka[1]; materialConfig->kAmbient[2] = ka[2]; };
	void setDiffuseConstant(float *kd) { materialConfig->kDiffuse[0] = kd[0]; materialConfig->kDiffuse[1] = kd[1]; materialConfig->kDiffuse[2] = kd[2]; };
	void setSpecularConstant(float *ks) { materialConfig->kSpecular[0] = ks[0]; materialConfig->kSpecular[1] = ks[1]; materialConfig->kSpecular[2] = ks[2]; };
	void setShininess(float s) {materialConfig->shininess = s; };
	
	void addBaseTexture(std::string& filename, int flags){ 
		Texture *t;
		t = TEXTUREMANAGER::getInstance().load(filename, Texture::TEXTURE_2D, Texture::RGB, Texture::RGB8, Texture::ANISOTROPIC_4);
		baseTextures.push_back(t);
	};
	
	virtual void initialize(std::string& filename) = 0;
	virtual void bind() = 0;
	virtual void unbind() = 0;
	
protected:

	MaterialData *materialConfig;
	
	std::string name;
	std::string shadername;
	bool hasShader;

	std::list<Texture *> baseTextures;
	
	
};

#endif //_MATERIAL_H_
