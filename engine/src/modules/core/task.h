#ifndef TASK_H_
#define TASK_H_

#include "../../util/memory/memoryManagedObject.h"

class Task : public MemoryManagedObject{
	
	public:
	
		Task(){ 
			canKill = false;
			priority = 5000;
		}
		
		virtual bool start(void* data)=0;
		virtual void onSuspend(void* data ){};
		virtual void update(void* data)=0;
		virtual void onResume(void* data){};
		virtual void stop(void* data ) = 0;

		bool canKill;
		long priority;
};

#endif /*TASK_H_*/
