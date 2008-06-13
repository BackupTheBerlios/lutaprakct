#ifndef SCENEDATA_H_
#define SCENEDATA_H_

#include "Mesh.h"
#include <cfxEffect.h>
#include <cfxMaterial.h>

//scenedata tem todos os maps (string, data) do collada. quando for carregar os nodes os objetos
// deles (meshes, lights, materials) sao ponteiros pros meshes do scenedata
struct SceneData{
	std::map<std::string, std::list<Mesh*> > instancedMeshes;
	std::map<std::string, cfxMaterial*>		cfxMaterials;
	std::map<std::string, cfxEffect*>		cfxEffects;
};

#endif /*SCENEDATA_H_*/
