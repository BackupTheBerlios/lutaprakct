
#include "memoryManagedObject.h"

std::list<MemoryManagedObject *> MemoryManagedObject::deadObjects;
std::list<MemoryManagedObject *> MemoryManagedObject::liveObjects;

MemoryManagedObject::MemoryManagedObject(){ 
	referenceCounter = 0;
	liveObjects.push_back(this); 
}

MemoryManagedObject::~MemoryManagedObject(){ 

}

void MemoryManagedObject::release(){
	referenceCounter--;
	if (referenceCounter <= 0){
		liveObjects.remove(this);
		deadObjects.push_back(this);
	}
}

void MemoryManagedObject::addReference(){
	referenceCounter++;
}

void MemoryManagedObject::collectGarbage(){
	
	for(std::list<MemoryManagedObject *>::iterator it=deadObjects.begin(); it!=deadObjects.end(); it++){
		MemoryManagedObject *o=(*it);
		delete o;
		it++;
	}
	deadObjects.clear();
}

void MemoryManagedObject::collectRemainingObjects(bool EmitWarnings){
	
	collectGarbage();
	for(std::list<MemoryManagedObject*>::iterator it=liveObjects.begin();it!=liveObjects.end();it++){
		
		MemoryManagedObject *o=(*it);
		if(EmitWarnings){
			//log it!
		}
		delete o;
	}
	liveObjects.clear();
}
