#ifndef KERNEL_H_
#define KERNEL_H_

#include "task.h"
#include "../../util/patterns/singleton.h"
#include "../../util/memory/memoryManagedObject.h"

class Kernel{
	
	public:
		Kernel();
		virtual ~Kernel();

		int execute();

		bool addTask(MemoryManagedPointer<Task> t);
		void suspendTask(MemoryManagedPointer<Task> t);
		void resumeTask(MemoryManagedPointer<Task> t);
		void removeTask(MemoryManagedPointer<Task> t);
		void killAllTasks();

	protected:
	
		std::list< MemoryManagedPointer<Task> > taskList;
		std::list< MemoryManagedPointer<Task> > pausedTaskList;
};

typedef singleton<Kernel> KERNEL;

#endif /*KERNEL_H_*/
