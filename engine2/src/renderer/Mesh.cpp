#include <iostream>
#include <dae.h>
#include <dom/domMaterial.h>
#include <dom/domGeometry.h>
#include <dom/domNode.h>
#include <dom/domCOLLADA.h>
#include "Mesh.h"
#include "../util/StringTokenizer.h"
#include "Renderer.h"

//duvidas: um triangles pode ter mais de uma tag input com mesma semantic? os vertices tbm?
Mesh::Mesh(domMesh* meshTag, std::map<std::string, cfxMaterial*>* cfxMaterials) {

	//pega todos os triangles TODO pegar lines, polys, tristrips e trifans tbm
	for (size_t k = 0; k < meshTag->getTriangles_array().getCount(); k++) {
		domTriangles* triangles = meshTag->getTriangles_array()[k];
		Triangles* tri = new Triangles;
		tri->materialName = triangles->getAttribute("material");
		tri->material = NULL;
		//memcpy(tri->material,(*cfxMaterials)[tri->materialName], sizeof(cfxMaterial) );
		tri->material = (*cfxMaterials)[tri->materialName];
		std::map<std::string, cfxMaterial*>::iterator iter3;
		std::cout << "setando material " << std::endl;
		std::cout << (*cfxMaterials).size() << std::endl;
		for (iter3 = (*cfxMaterials).begin(); iter3 != (*cfxMaterials).end(); iter3++) {
			std::cout << (*iter3).first << std::endl;
			if ((*iter3).first == tri->materialName) {
				std::cout << "Adicionando material " << std::endl;
				tri->material = (*iter3).second;
				//std::cout << tri->materialName << " " << (*iter3).second->getName() << std::endl;
				if (!(*iter3).second)
					std::cout << "nao tem mesmo " << std::endl;
			}
		}
		std::cout << "done " << std::endl;
		//std::cout << (*iter3).first  << std::endl;
		if (tri->material != NULL)
			std::cout << "ttem material" << std::endl;
		else
			std::cout << "nao tem material "
					<< triangles->getAttribute("material") << std::endl;
		tri->count = atoi(triangles->getAttribute("count").c_str())*3;
		tri->triangles = new unsigned int[tri->count];
		domP* p = triangles->getP();
		StringTokenizer tokenizer(p->getCharData(), " ");
		for (size_t i = 0; i < tri->count; i++) {
			std::string token;
			tokenizer.nextToken(token);
			tri->triangles[i] = (unsigned int)atoi(token.c_str());
		}

		//pegou os indices dos triangles, agora pega as outras info
		for (size_t i = 0; i < triangles->getInput_array().getCount(); i++) {
			domInputLocalOffset *input = triangles->getInput_array()[i];
			std::string semantic = input->getAttribute("semantic");// ->getAttribute("semantic");
			if (semantic == "VERTEX") {
				domVertices* vertices =
						(domVertices*) (domElement*) input->getSource().getElement();
				for (size_t l = 0; l < vertices->getInput_array().getCount(); l++) {
					domInputLocal* vertexInput = vertices->getInput_array()[l];
					std::string nsemantic = vertexInput->getSemantic();
					if (nsemantic == "POSITION") {
						domSource
								* positions =
										(domSource*) (domElement*) vertexInput->getSource().getElement();
						domFloat_array* values = positions->getFloat_array();
						tri->verticesCount = values->getCount();
						//std::cout << tri->verticesCount << std::endl;
						tri->vertices = new float[tri->verticesCount];
						StringTokenizer tokenizer(values->getCharData(), " ");
						for (size_t n = 0; n < tri->verticesCount; n++) {
							std::string token;
							tokenizer.nextToken(token);
							//std::cout << atof(token.c_str()) << std::endl;
							tri->vertices[n] = atof(token.c_str());
							//std::cout << tri->vertices[n] << std::endl;
						}
					}
				}
			} else if (semantic == "NORMAL") {

				domSource* normals =
						(domSource*) (domElement*)input->getSource().getElement();
				domFloat_array* values = normals->getFloat_array();
				tri->normalsCount = values->getCount();
				tri->normals = new float[tri->normalsCount];
				StringTokenizer tokenizer(values->getCharData(), " ");
				for (size_t n = 0; n < tri->normalsCount; n++) {
					std::string token;
					tokenizer.nextToken(token);
					//std::cout << atof(token.c_str()) << std::endl;
					tri->normals[n] = atof(token.c_str());
					//std::cout << tri->vertices[n] << std::endl;
				}
			} else if (semantic == "TEXCOORD") {

			}
		}

		tris.push_back(tri);

	}

	createVBO();

}

void Mesh::render() {

	std::list<Triangles*>::iterator i;
	for (i = tris.begin(); i != tris.end(); i++) {
		bindMaterial((*i));
		RENDERER::getInstance().drawVBO((*i)->vertexID, (*i)->normalID, (*i)->indicesID, (*i)->count);
	}

}

void Mesh::createVBO() {
	std::list<Triangles*>::iterator i;
	for (i = tris.begin(); i != tris.end(); i++) {
		(*i)->vertexID = RENDERER::getInstance().initializeVBO((*i)->verticesCount*sizeof(float), (*i)->vertices);
		(*i)->normalID = RENDERER::getInstance().initializeVBO((*i)->normalsCount*sizeof(float), (*i)->normals);
		(*i)->indicesID = RENDERER::getInstance().initializeVBO((*i)->count*sizeof(unsigned int), (*i)->triangles);
	}
}

void Mesh::destroyVBO() {
	std::list<Triangles*>::iterator i;
	for (i = tris.begin(); i != tris.end(); i++) {
		RENDERER::getInstance().killVBO((*i)->vertexID);
		RENDERER::getInstance().killVBO((*i)->normalID);
	}
}

void Mesh::bindMaterial(Triangles* tri) {

	if (!tri->material)
		return;

	tri->material->setParameterValues();
	cfxEffect* currentEffect = tri->material->getEffect();

	//configura os parametros default do Cg. pode ser necessario configurar mais
	CGparameter worldviewprojectionParam =
			currentEffect->getParameterBySemantic("WORLDVIEWPROJECTION");
	CGparameter viewinverseParam =
			currentEffect->getParameterBySemantic("VIEWINVERSE");
	CGparameter worldParam = currentEffect->getParameterBySemantic("WORLD");
	CGparameter worldinversetransposeParam =
			currentEffect->getParameterBySemantic("WORLDINVERSETRANSPOSE");
	CGparameter lightPositionParam =
			currentEffect->getParameterBySemantic("LIGHTPOSITION");
	CGparameter timeParam = currentEffect->getParameterBySemantic("TIME");

	//TODO fazer essa parte das matrizes
	// WORLDVIEWPROJECTION is the world+view+projection matrix of this object which we get from GL
	/*if (worldviewprojectionParam) {
	 cgGLSetStateMatrixParameter(worldviewprojectionParam, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	 }

	 // VIEWINVERSE is the inverse of the view matrix which is the same as the camera's LocalToWorldMatrix
	 if (viewinverseParam) {
	 CrtInstanceCamera *inst = _CrtRender.GetActiveInstanceCamera();
	 cgGLSetMatrixParameterfc(viewinverseParam,
	 (const float *)(inst->Parent->GetLocalToWorldMatrix()));
	 }

	 // WORLD is the localtoworld matrix for this object which we get from the scene graph
	 if (worldParam) {
	 cgGLSetMatrixParameterfc(worldParam,
	 (const float *)(parentNode->GetLocalToWorldMatrix()));
	 //			cgGLSetStateMatrixParameter(worldParam, CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_IDENTITY);
	 }

	 // WORLDINVERSETRANSPOSE is inversetransposelocaltoworld matrix for this object from the scene graph
	 if (worldinversetransposeParam) {
	 cgGLSetMatrixParameterfc(
	 worldinversetransposeParam,
	 (const float *)(parentNode->GetInverseTransposeLocalToWorldMatrix()));
	 //			cgGLSetStateMatrixParameter(worldinversetransposeParam, CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_INVERSE);
	 }*/

	// LIGHTPOSITION gets the position of the primary (nearist) light
	if (lightPositionParam) {
		//CrtInstanceLight *instanceLight =_CrtRender.GetScene()->GetLightInstances(0);
		// Get the light position from the light instance's parent node's LocalToWorldMatrix
		// REFACTOR IN PROGRESS we should have an accessor for getting the position
		//float *lightMatrix = (float *)instanceLight->Parent->GetLocalToWorldMatrix();

		CGtype lighttype = cgGetParameterType(lightPositionParam);
		if (lighttype == CG_FLOAT3) {
			//cgSetParameter3f(lightPositionParam, lightMatrix[12], lightMatrix[13], lightMatrix[14]);
			cgSetParameter3f(lightPositionParam, 0.0, 0.0, 0.0);
		} else if (lighttype == CG_FLOAT4) {
			//cgSetParameter4f(lightPositionParam, lightMatrix[12], lightMatrix[13], lightMatrix[14], 0);
			cgSetParameter4f(lightPositionParam, 0.0, 0.0, 0.0, 0);
		}
	}

	// TODO pegar o timer
	//if (timeParam) {
	//	cgSetParameter1f(timeParam, ticker);
	//}

	// Setup the state for the cfxMaterial
	tri->material->setEffectPassState(0, 0);
}