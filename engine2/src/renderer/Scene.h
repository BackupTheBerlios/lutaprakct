#ifndef SCENE_H_
#define SCENE_H_

#include <string>
#include <map>
#include "Node.h"

class Scene{
	
public:
	
	Scene(){ initialize(); }
	void initialize();
	void update();
	void render();
	
	bool load(char* filename);
	
	Geometry		*ReadGeometry( domGeometryRef lib);
	Node			*ReadNode( domNodeRef node, Node * parentNode );
	
	DAE* collada;
	CrtNode* sceneRoot;
	
	std::string filename;
	
	std::vector<Geometry*>	geometries;
	std::map<std::string, Node *> Nodes;
	
};

#endif /*SCENE_H_*/
