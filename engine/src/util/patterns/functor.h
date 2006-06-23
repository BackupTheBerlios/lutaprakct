#ifndef FUNCTOR_H_
#define FUNCTOR_H_

#include "../memory/memoryManagedObject.h"

/* um simples functor para apontar para fun?oes membros de um objeto. talvez seja
 * melhor usar functor da STL ;) 
 */

class Functor : public MemoryManagedObject{
	
	public:
		virtual void operator ()()=0;
	
};

template<class T>
class ObjectFunctor : public Functor{
	
	protected:
		T *object;
		typedef void (T::*funcType)();
		funcType func;
		
	public:
		AUTO_SIZE;
   
		ObjFunctor(T *o, funcType f) { object=o; func=f; }
   
		void operator ()()  { (object->*func)(); }
};

#endif /*FUNCTOR_H_*/
