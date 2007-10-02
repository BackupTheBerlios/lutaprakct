
#include <iostream>
#include <stdlib.h>
#include "ColladaIO.h"
#include "../patterns/StringTokenizer.h"

bool ColladaIO::load(char* filename){
	
	//tenta ler o arquivo do modelo
	TiXmlDocument modeldoc(filename);
	if (!modeldoc.LoadFile()){
		modeldoc.Clear();
		std::cout << "Erro: filename not found: " << filename << std::endl;
		return false;
	}
	
	//procura pela tag COLLADA
	TiXmlElement* colladatag = modeldoc.FirstChildElement("COLLADA");
	if (!colladatag){
		modeldoc.Clear();
		std::cout << "Erro: Tag Collada not found. " << std::endl;
		return false;
	}
	
	//le a parte do arquivo que organiza a cena, na cena que ficam a lista de objetos (nodes)
	TiXmlElement* librarySceneTag = colladatag->FirstChildElement("library_visual_scenes");
	if (!librarySceneTag){
		modeldoc.Clear();
		std::cout << "Erro: Tag library_visual_scenes not found." << std::endl;
		return false;
	}

	readNodes(colladatag);	
		
	modeldoc.Clear();
	return true;
}

void ColladaIO::readGeometry(std::string url, TiXmlElement* tag){

	TiXmlElement* libraryGeometryTag = NULL;
	libraryGeometryTag = tag->FirstChildElement("library_geometries");
	if (!libraryGeometryTag){
		std::cout << "Erro: Tag library_geometries not found." << std::endl;
		return;
	}
	
	TiXmlElement* geometryTag = NULL;
	geometryTag = libraryGeometryTag->FirstChildElement("geometry");

	//le cada tag geometry da cena
	//TODO criar um map ao inves de percorrer todos toda vez pra tornar mais rapido
	while(geometryTag){
		
		std::string geometryId = geometryTag->Attribute("id");
		std::cout << geometryId << std::endl;
		if (geometryId == url){
		
			TiXmlElement* meshTag = NULL;
			
			meshTag = geometryTag->FirstChildElement("mesh");
			ColladaMeshData* mesh;
			if (meshTag){
				//procura pela tag triangles
				TiXmlElement* trianglesTag = NULL;
				trianglesTag = meshTag->FirstChildElement("triangles");
				
				while (trianglesTag){
					mesh = new ColladaMeshData();
					TiXmlElement* sourceTag = NULL;
					sourceTag = meshTag->FirstChildElement("source");
					mesh->ntextures = getNumberOfTextures(trianglesTag);
					readIndices(trianglesTag, mesh);
					
					TiXmlElement* inputTag = trianglesTag->FirstChildElement("input");
					//TODO talvez seja bom buscar a geometry pela url/id dela
					while (inputTag){
						std::string semantic = inputTag->Attribute("semantic");
						std::string source = inputTag->Attribute("source");
						source.erase(0, 1);
						if ( semantic ==  "VERTEX"  ){
							readVertices(sourceTag, mesh, source);
						}else if ( semantic == "NORMAL" ){
							readNormals(sourceTag, mesh, source);
						}else if (semantic == "TEXCOORD" ){
							mesh->ntextures++;
							readTexcoords(sourceTag, mesh, source, atoi(inputTag->Attribute("set")));
						}
						inputTag = inputTag->NextSiblingElement("input");
					}
					//readMaterial(trianglesTag, colladatag, mesh);
					
					meshes.push_back(mesh);
					trianglesTag = trianglesTag->NextSiblingElement("triangles"); 
				}
				geometryTag = geometryTag->NextSiblingElement("geometry");
			}
		}
	}

}

void ColladaIO::readNodes(TiXmlElement* tag){


	TiXmlElement* librarySceneTag = tag->FirstChildElement("library_visual_scenes");
	if (!librarySceneTag){
		std::cout << "Erro: Tag library_visual_scenes not found." << std::endl;
		return;
	}

	TiXmlElement* visualSceneTag = NULL;
	visualSceneTag = librarySceneTag->FirstChildElement("visual_scene");
	if (!visualSceneTag){
		std::cout << "Erro: Tag visual_scene not found." << std::endl;
		return;
	}	

	std::list<ColladaNode*> geometryNodes;

	while (visualSceneTag){

		TiXmlElement* nodeTag = NULL;
		nodeTag = visualSceneTag->FirstChildElement("node");
		//TODO dentro da tag node pode ter varias outras tags nos precisa usar uma pilha
		//ou fazer recursivo
		while (nodeTag){
			TiXmlElement* instanceGeometryTag = NULL;
			instanceGeometryTag = nodeTag->FirstChildElement("instance_geometry");
			if (instanceGeometryTag){ //se for um no de geometria
				std::cout << "tem geometry" << std::endl;
				ColladaNode* node = new ColladaNode;
				node->geometryUrl = instanceGeometryTag->Attribute("url");
				node->geometryUrl = node->geometryUrl.erase(0, 1);
				
/*				TiXmlElement* bindMaterialNode = NULL;
				bindMaterialNode = instanceGeometryTag->FirstChildElement("bind_material");
				while (bindMaterialNode){
					TiXmlElement* techniqueCommonTag = NULL;
					techniqueCommonTag = instanceGeometryTag->FirstChildElement("technique_common");
					if (techniqueCommonTag){
						TiXmlElement* instanceMaterialTag = NULL;
						instanceMaterialTag =  techniqueCommonTag->FirstChildElement("instance_material");
						if (instanceMaterialTag){
							InstanceMaterial* material = new InstanceMaterial; 
							material->symbol = instanceMaterialTag->Attribute("symbol");
							material->target = instanceMaterialTag->Attribute("target");
							
							//TiXmlElement*
							node->materials.push_back(material);
						}
					}
					bindMaterialNode = bindMaterialNode->NextSiblingElement("bind_material");
				}*/
				geometryNodes.push_back(node);	
			}
			nodeTag = nodeTag->NextSiblingElement("node"); 
		}
		visualSceneTag = visualSceneTag->NextSiblingElement("visual_scene");
	}
	
	std::list<ColladaNode*>::iterator iter;
	for (iter = geometryNodes.begin(); iter != geometryNodes.end(); iter++){
		readGeometry((*iter)->geometryUrl, tag);
	}
	
}

void ColladaIO::readMaterial(TiXmlElement* tag, TiXmlElement* colladaTag, ColladaMeshData* mesh){

	std::string materialName = tag->Attribute("material");
	if (materialName.length() <= 0)
		return;
		
	TiXmlElement* libraryMaterialTag = NULL;
	libraryMaterialTag = colladaTag->FirstChildElement("library_materials");
	if (libraryMaterialTag){
		
	}
	
}

void ColladaIO::readVertices(TiXmlElement* sourceTag, ColladaMeshData* mesh, std::string source){

	int i;
	std::string token;
	std::cout << "lendo vertices" << std::endl;
	while (sourceTag){
		std::string name = sourceTag->Attribute("name");
		//std::cout << name << std::endl;
		if (name == "position"){
			TiXmlElement* floatArrayTag = sourceTag->FirstChildElement("float_array");
			//le a strign de vertices, aloca a memoria e copia
			if (floatArrayTag){
				std::string floatarray = floatArrayTag->FirstChild()->Value();
				mesh->vertexdata = new float[atoi(floatArrayTag->Attribute("count"))];
				floatarray.insert(0, " ");
				floatarray.insert(floatarray.length(), " " );
				StringTokenizer vertTokenizer(floatarray, " ");
				i = 0;
				while (vertTokenizer.hasMoreTokens()){
					vertTokenizer.nextToken(token);
					mesh->vertexdata[i] = atof( token.c_str() );
					i++;
				} 
			}
		}
				
		sourceTag = sourceTag->NextSiblingElement("source");
	}
	
}

void ColladaIO::readNormals(TiXmlElement* sourceTag, ColladaMeshData* mesh, std::string source){

	int i;
	std::string token;
	
	while (sourceTag){
		std::string name = sourceTag->Attribute("id");
		//std::cout << name << std::endl;
		if (name == source){
			TiXmlElement* floatArrayTag = sourceTag->FirstChildElement("float_array");
			//le a strign de vertices, aloca a memoria e copia
			if (floatArrayTag){
				std::string floatarray = floatArrayTag->FirstChild()->Value();
				mesh->normaldata = new float[atoi(floatArrayTag->Attribute("count"))];
				floatarray.insert(0, " ");
				floatarray.insert(floatarray.length(), " " );
				StringTokenizer vertTokenizer(floatarray, " ");
				i = 0;
				while (vertTokenizer.hasMoreTokens()){
					vertTokenizer.nextToken(token);
					mesh->normaldata[i] = atof( token.c_str() );
					i++;
				} 
			}
		}
				
		sourceTag = sourceTag->NextSiblingElement("source");
	}
	
}

void ColladaIO::readTexcoords(TiXmlElement* sourceTag, ColladaMeshData* mesh, std::string source, int set){

	int i;
	std::string token;
	
	while (sourceTag){
		std::string id = sourceTag->Attribute("id");
		//std::cout << name << std::endl;
		if (id == source){
			TiXmlElement* floatArrayTag = sourceTag->FirstChildElement("float_array");
			//le a strign de vertices, aloca a memoria e copia
			if (floatArrayTag){
				std::string floatarray = floatArrayTag->FirstChild()->Value();
				mesh->texcoords[set] = new float[atoi(floatArrayTag->Attribute("count"))];
				floatarray.insert(0, " ");
				floatarray.insert(floatarray.length(), " " );
				StringTokenizer vertTokenizer(floatarray, " ");
				i = 0;
				while (vertTokenizer.hasMoreTokens()){
					vertTokenizer.nextToken(token);
					mesh->texcoords[set][i] = atof( token.c_str() );
					i++;
				} 
			}
		}
				
		sourceTag = sourceTag->NextSiblingElement("source");
	}
	
}


/* os modelos collada possuem 1 array de indices para cada informacao geometrica.
 * um array de indices pra posicoes dos vertices ,pras normais, pras texcoords, tangents, etc
 * essa versao do readIndices leva em conta que foi utilizado o conditioner deindexer
 * que vem com o collada refinary, para organizar os arrays de indices em apenas um array
 * se nao for utilizado o conditioner essa funcao nao funciona
 * */ 
void ColladaIO::readIndices(TiXmlElement* trianglesTag, ColladaMeshData* mesh){

	mesh->nindices = atoi(trianglesTag->Attribute("count"))*3;
			
	//std::cout << "indices" << mesh->nindices << std::endl;
			
	//aloca os espaco do vetor de indices
	mesh->indices = new unsigned int[mesh->nindices];
			
	//le os indices
	TiXmlElement* pTag = NULL;
	pTag = trianglesTag->FirstChildElement("p");
	std::string indices;
	if (pTag->FirstChild())
		indices = pTag->FirstChild()->Value();
				
	//adiciona espaco no comeco e fim da string pra usar o tokenizer
	indices.insert(0, " ");
	indices.insert(indices.length(), " ");
	StringTokenizer tokenizer(indices, " ");

	unsigned int i = 0;
	std::string token;
	while (tokenizer.hasMoreTokens()){
		tokenizer.nextToken(token);
		//std::cout << token << std::endl;
		mesh->indices[i] = atoi( token.c_str() );
		i++;
	}
			
	//std::cout << "indices " << indices << std::endl;
			
	//depois de lido os indices, olha os offsets
	//TODO olhar outros alem de vertices
	// ISSO NAO EH MAIS FEITO
//	unsigned int input = getNumberOfInputs(trianglesTag);
//	unsigned int vertexOffset = getVertexOffset(trianglesTag);
			
	//passa TODOS os indices pra um array
/*	unsigned int* allindices = new unsigned int [tokenizer.countTokens()];
	unsigned int i = 0;
	std::string token;
	while (tokenizer.hasMoreTokens()){
		tokenizer.nextToken(token);
		//std::cout << token << std::endl;
		allindices[i] = atoi( token.c_str() );
		i++;
	} 
			
	//le agora apenas os indices
	int vertIndice = vertexOffset;
	for (i = 0; i < mesh->nindices; i++){
		mesh->indices[i] = allindices[vertIndice];
		//std::cout << "indice " << mesh->indices[i] << std::endl;
		vertIndice += input;
	}
	
	delete allindices;*/
}

unsigned int ColladaIO::getNumberOfInputs(TiXmlElement* tag){

	unsigned int value = 0;
	
	TiXmlElement* token = NULL;
	token = tag->FirstChildElement("input");
	while(token){
		value++;
		token = token->NextSiblingElement("input");
	}
	
	return value;
	
}

unsigned int ColladaIO::getNumberOfTextures(TiXmlElement* tag){

	unsigned int i = 0;
	
	TiXmlElement* input = tag->FirstChildElement("input");
	
	while (input){
		std::string semantic = input->Attribute("semantic");
		if (semantic == "TEXCOORD")
			i++;
		input = input->NextSiblingElement("input");	
	}
	
	return i;
}

unsigned int ColladaIO::getVertexOffset(TiXmlElement* triangles){

	TiXmlElement* inputTag = NULL;
	inputTag = triangles->FirstChildElement("input");
	
	while (inputTag){
		std::string semantic;
		semantic = inputTag->Attribute("semantic");
		if ( semantic == "VERTEX")
			return atoi( inputTag->Attribute("offset") );
	}
	
	return 0;
}


