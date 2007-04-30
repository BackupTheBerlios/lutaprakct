#ifndef _LIGHTMANAGER_H_
#define _LIGHTMANAGER_H_

#include "light.h"
#include <list>
#include "../../util/patterns/singleton.h"

//classe q possui a lista de luzes. no futuro sera usada para o lighting culling

class LightManager{
	
public:

	LightManager(){};
	~LightManager(){};

	void add(Light *light){
		lights.push_back(light);
	}
	
	void remove(unsigned int id){
		std::list<Light* >::iterator iter;
		for (iter = lights.begin(); iter != lights.end(); iter++){
			if ( (*iter)->getId() == id){
				(*iter)->shutdown();
			}
		}
	}
	
	void bind(){
		std::list<Light*>::iterator iter;
		for (iter = lights.begin(); iter != lights.end(); iter++)
			(*iter)->bind();
	}
	
	void unbind(){
		std::list<Light*>::iterator iter;
		for (iter = lights.begin(); iter != lights.end(); iter++)
			(*iter)->unbind();
	}	

private:
	
	std::list<Light* > lights;
	
};

typedef Singleton<LightManager> LIGHTMANAGER;

#endif //_LIGHTMANAGER_H_
