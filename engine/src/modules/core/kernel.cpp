

#include "kernel.h"
#include "../../util/profiler/profiler.h"

Kernel::Kernel(){
}

Kernel::~Kernel(){
}

int Kernel::execute(){

	while(taskList.size()){
		{
			PROFILE("Kernel task loop");

			std::list< MemoryManagedPointer<Task> >::iterator it;
			for(it=taskList.begin();it!=taskList.end();){
				Task *t=(*it);
				it++;
				if(!t->canKill)t->update();
			}
			
			//loop again to remove dead tasks
			for(it=taskList.begin();it!=taskList.end();){
				Task *t=(*it);
				it++;
				if(t->canKill){
					t->stop();
					taskList.remove(t);
					t=0;
				}
			}
			
			MemoryManagedObject::collectGarbage();
		}
#ifdef _DEBUG
		ProfileSample::output();
#endif
	}

	return 0;
}

bool Kernel::addTask(MemoryManagedPointer<Task> t){
	
	if(!t->start())return false;

	//keep the order of priorities straight
	std::list< MemoryManagedPointer<Task> >::iterator it;
	for(it=taskList.begin();it!=taskList.end();it++){
		MemoryManagedPointer<Task> &comp=(*it);
		if(comp->priority>t->priority)break;
	}
	taskList.insert(it,t);
	return true;
}

void Kernel::suspendTask(MemoryManagedPointer<Task> t){
	//check that this task is in our list - we don't want to suspend a task that isn't running
	if(std::find(taskList.begin(),taskList.end(),t)!=taskList.end()){
		t->onSuspend();
		taskList.remove(t);
		pausedTaskList.push_back(t);
	}
}

void Kernel::resumeTask(MemoryManagedPointer<Task> t){
	
	if(std::find(pausedTaskList.begin(),pausedTaskList.end(),t)!=pausedTaskList.end()){
		t->onResume();
		pausedTaskList.remove(t);
		//keep the order of priorities straight
		std::list< MemoryManagedPointer<Task> >::iterator it;
		for(it=taskList.begin();it!=taskList.end();it++){
			MemoryManagedPointer<Task> &comp=(*it);
			if(comp->priority>t->priority)break;
		}
		taskList.insert(it,t);
	}
}

void Kernel::removeTask(MemoryManagedPointer<Task> t){
	
	if(std::find(taskList.begin(),taskList.end(),t)!=taskList.end()){
		t->canKill=true;
	}
}

void Kernel::killAllTasks(){
	
	for(std::list< MemoryManagedPointer<Task> >::iterator it=taskList.begin();it!=taskList.end();it++){
		(*it)->canKill=true;
	}
}
