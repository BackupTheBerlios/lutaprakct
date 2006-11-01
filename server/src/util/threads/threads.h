#ifndef _THREADS_H_
#define _THREADS_H_

#include "../errors/exceptions.h"

namespace threads{

//#define MODIFIER

	unsigned int Ticks();
	void Delay(unsigned int dur);
	unsigned short ShortEndian(unsigned short endi);
	unsigned int LongEndian(unsigned int endi);
	
	class Thread{
		typedef void* (/*MODIFIER*/ *ThreadProc) (void*);
		
		private:
			const ThreadProc proc;
			pthread_t handle;
			
		public:
			Thread(ThreadProc MyProc) : proc(MyProc) { };
			void run(void *args) throw(errors::Exception);
			~Thread(){};
	};
	
}


#endif //_THREADS_H_
