#ifndef TASK_H_
#define TASK_H_

#include "../../util/memory/memoryManagedObject.h"

class Task : public MemoryManagedObject{
	
	public:
	
		Task(){ 
			canKill = false;
			priority = 5000;
		}
		
		virtual bool start()=0;
		virtual void onSuspend(){};
		virtual void update()=0;
		virtual void onResume(){};
		virtual void stop()=0;

		bool canKill;
		long priority;
};

#endif /*TASK_H_*/
