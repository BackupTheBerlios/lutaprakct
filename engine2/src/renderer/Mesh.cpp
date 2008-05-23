#include <dae.h>
#include <dom/domMaterial.h>
#include <dom/domGeometry.h>
#include <dom/domNode.h>
#include <dom/domCOLLADA.h>
#include "Mesh.h"
#include "../util/StringTokenizer.h"

Mesh::Mesh(domMesh* meshTag){
	
	//pega todos os triangles
	for(size_t k = 0; k < meshTag->getTriangles_array().getCount(); k++){
		domTriangles* triangles = meshTag->getTriangles_array()[k];
		Triangles* tri = new Triangles;
		tri->count = atoi(triangles->getAttribute("count").c_str());
		tri->triangles = new unsigned int[tri->count];
		domP* p = triangles->getP();
		StringTokenizer tokenizer(p->getCharData(), " ");
		int i = 0;
		while (tokenizer.hasMoreTokens()){
			std::string token;
			tokenizer.nextToken(token);
			tri->triangles[i] = (unsigned int)atof(token.c_str());
		}
		//pegou os indices dos triangles, agora pega as outras info
		for(size_t i = 0; i < triangles->getInput_array().getCount(); i++){
			domInputLocalOffset *input = triangles->getInput_array()[i];
			std::string semantic = input->getAttribute("semantic");
			if (semantic == "VERTEX"){
				
			}
				
		}
		
	}
	
	
}