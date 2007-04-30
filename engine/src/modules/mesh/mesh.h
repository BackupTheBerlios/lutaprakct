#ifndef _MESH_H_
#define _MESH_H_

#include "../../util/math/algebra.h"
#include "meshData.h"
#include "meshrenderer/meshRenderer.h"
#include "../material/material.h"
#include <string>

/* mesh eh formado por mesh data (info geometrica do modelo) + renderer (de acordo
 * com o tipo de mesh precisa de um renderer diferente) + material + gamedata.
 * 
 * meshdata: eh gerenciado por um singleton. so fica 1 na memoria para cada modelo
 * renderer: eh criado um por objeto (talvez fazer 1 por modelo tbm)
 * material: eh gerenciado e so cria 1 por modelo tbm, eh aplicado antes do draw
 * gamedata: eh criado um por objeto. essa classe so possui o basico, eh aqui que
 * fica informacoes sobre a posicao do objeto e status dele no mundo. precisa ser
 * extendido dependendo do game
 * */

class Mesh{
	
public:

	Mesh();
	Mesh(std::string filename, int flags = 0);
	virtual ~Mesh();
	
	bool initialize(std::string filename, int flags = 0);
	
	void setMaterial(Material* m){meshMaterial = m;}
	
	//as funcoes abaixo modificam a matriz do objeto
	void rotate(float angle, float x, float y, float z);
	void rotate(float angle, vec3 axis);
	
	void translateAdd(float x, float y, float z );
	void translateTo(float amount, vec3 axis);
	void translateTo(float x, float y, float z);
	
	void scale(float x, float y, float z);
	void scaleAdd(float x, float y, float z);

	vec3 getPosition();
	vec3 getScale();

	void draw();
	void draw(int frame);
	void draw(float elapsedTime, int startframe, int endframe);

	void update();
	void update(float elapsedTime);

private:

	int discoverRenderType();

	MeshData* meshdata;
	MeshRenderer* renderer;
	mat4 modelview;
	Material* meshMaterial;
	
	float time;
};


#endif //_MESH_H_
