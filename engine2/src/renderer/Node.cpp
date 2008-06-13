#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <dae/daeURI.h>

template<typename MyType, typename DomType>
MyType& lookup(DomType& domObject) {
	if (!domObject.getUserData())
		domObject.setUserData(new MyType(domObject));
	return *(MyType*)(domObject.getUserData());
}

void Node::render(){
	
	//push na matrix
	//multi na matrix pela matrix do node
	std::list<Mesh*>::iterator iter;
	
	for(iter = meshes.begin(); iter != meshes.end(); iter++){
		(*iter)->render();
	}
	
}

Node::Node(domNode& node, SceneData *scenedata) {
	// Recursively convert all child nodes. First iterate over the <node> elements.
	for (size_t i = 0; i < node.getNode_array().getCount(); i++){
		Node* n = new Node(*node.getNode_array()[i], scenedata);
		childNodes.push_back(n);
	}

	// Then iterate over the <instance_node> elements.
	//TODO colocar instance_node depois
	/*for (size_t i = 0; i < node.getInstance_node_array().getCount(); i++) {
		domNode* child = daeSafeCast<domNode>(
			node.getInstance_node_array()[i]->getUrl().getElement());
			childNodes.push_back(&lookup<Node, domNode>(*child));
	}*/

	// Iterate over all the <instance_geometry> elements
	for (size_t i = 0; i < node.getInstance_geometry_array().getCount(); i++) {
		domInstance_geometry* instanceGeom = node.getInstance_geometry_array()[i];
		
		
		//std::cout << "url " << instanceGeom->getUrl().id() << std::endl;
		std::string a = instanceGeom->getUrl().id();
		if (scenedata->instancedMeshes[a].size() > 0 ){
			std::cout << "adicionado mesh" << std::endl;
			std::list<Mesh*>::iterator iter;
			for (iter = scenedata->instancedMeshes[a].begin(); iter != scenedata->instancedMeshes[a].end(); iter++ ){
				meshes.push_back(*iter);
			}
		}
			//std::cout << "Tem o mesh" << std::endl;
		
		//domGeometry* geom = daeSafeCast<domGeometry>(instanceGeom->getUrl().getElement());
		//domMesh* meshTag = geom->getMesh(); //so tem um mesh sempre?
		
		//std::cout << "mesh url " << meshTag->getID() << std::endl; 
		//Mesh* mesh = new Mesh(meshTag);
		//meshes.push_back(mesh);
		
		// Lookup the material that we should apply to the <geometry>. In a real app
		// we'd need to worry about having multiple <instance_material>s, but in this
		// test let's just convert the first <instance_material> we find.
		//domInstance_material* instanceMtl = daeSafeCast<domInstance_material>(
		//	instanceGeom->getDescendant("instance_material"));
		//domMaterial* mtl = daeSafeCast<domMaterial>(instanceMtl->getTarget().getElement());
		//Material& convertedMtl = lookup<Material, domMaterial>(*mtl);


		//meshes.push_back(&lookup<Mesh, domGeometry>(*geom));
		//meshes.back()->mtl = &convertedMtl;
	}
}
