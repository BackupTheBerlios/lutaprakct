#ifndef KERNEL_H_
#define KERNEL_H_

#include "task.h"
#include "../../util/patterns/singleton.h"
#include "../../util/memory/memoryManagedObject.h"
#include "../events/eventhandler.h"

class Kernel : public EventHandler{
	
	public:
		Kernel();
		virtual ~Kernel();

		int execute();

		bool addTask(MemoryManagedPointer<Task> t);
		void suspendTask(MemoryManagedPointer<Task> t);
		void resumeTask(MemoryManagedPointer<Task> t);
		void removeTask(MemoryManagedPointer<Task> t);
		void killAllTasks();
		void handleEvent(const event &e);

	protected:
	
		std::list< MemoryManagedPointer<Task> > taskList;
		std::list< MemoryManagedPointer<Task> > pausedTaskList;
};

typedef Singleton<Kernel> KERNEL;

#endif /*KERNEL_H_*/
