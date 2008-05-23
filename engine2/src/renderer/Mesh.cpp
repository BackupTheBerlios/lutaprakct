#include <iostream>
#include <dae.h>
#include <dom/domMaterial.h>
#include <dom/domGeometry.h>
#include <dom/domNode.h>
#include <dom/domCOLLADA.h>
#include "Mesh.h"
#include "../util/StringTokenizer.h"

//duvidas: um triangles pode ter mais de uma tag input com mesma semantic? os vertices tbm?
Mesh::Mesh(domMesh* meshTag){
	
	
	//pega todos os triangles TODO pegar lines, polys, tristrips e trifans tbm
	for(size_t k = 0; k < meshTag->getTriangles_array().getCount(); k++){
		domTriangles* triangles = meshTag->getTriangles_array()[k];
		Triangles* tri = new Triangles;
		tri->count = atoi(triangles->getAttribute("count").c_str())*3;
		tri->triangles = new unsigned int[tri->count];
		domP* p = triangles->getP();
		StringTokenizer tokenizer(p->getCharData(), " ");
		for(size_t i = 0; i < tri->count; i++){
			std::string token;
			tokenizer.nextToken(token);
			tri->triangles[i] = (unsigned int)atof(token.c_str());
		}
		
		//pegou os indices dos triangles, agora pega as outras info
		for(size_t i = 0; i < triangles->getInput_array().getCount(); i++){
			domInputLocalOffset *input = triangles->getInput_array()[i];
			std::string semantic = input->getAttribute("semantic");// ->getAttribute("semantic");
			if (semantic == "VERTEX"){
				domVertices* vertices = (domVertices*) (domElement*) input->getSource().getElement();
				for (size_t l = 0; l < vertices->getInput_array().getCount(); l++ ){
					domInputLocal* vertexInput = vertices->getInput_array()[l];
					std::string nsemantic = vertexInput->getSemantic();
					if ( nsemantic  == "POSITION"){
						domSource* positions = (domSource*) (domElement*) vertexInput->getSource().getElement();
						domFloat_array* values = positions->getFloat_array();
						tri->verticesCount = values->getCount();
						//std::cout << tri->verticesCount << std::endl;
						tri->vertices = new float[tri->verticesCount];
						StringTokenizer tokenizer(values->getCharData(), " ");
						for(size_t n = 0; n < tri->verticesCount; n++){
							std::string token;
							tokenizer.nextToken(token);
							//std::cout << atof(token.c_str()) << std::endl;
							tri->vertices[n] = atof(token.c_str());
							//std::cout << tri->vertices[n] << std::endl;
						}
					}
				}
			}else if (semantic == "NORMAL"){
				
				domSource* normals = (domSource*) (domElement*)input->getSource().getElement();
				domFloat_array* values = normals->getFloat_array();
				tri->normalsCount = values->getCount();
				tri->normals = new float[tri->normalsCount];
				StringTokenizer tokenizer(values->getCharData(), " ");
				for(size_t n = 0; n < tri->normalsCount; n++){
					std::string token;
					tokenizer.nextToken(token);
					//std::cout << atof(token.c_str()) << std::endl;
					tri->normals[n] = atof(token.c_str());
					//std::cout << tri->vertices[n] << std::endl;
				}				
			}else if (semantic == "TEXCOORD"){
			
				
				
			}	
		}
		
		
		tris.push_back(tri);
		
	}
	
	
}
