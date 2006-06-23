#ifndef MEMORYMANAGEDOBJECT_H_
#define MEMORYMANAGEDOBJECT_H_

#include <list>
#include <cassert>

/* objeto base da hierarquia. */

class MemoryManagedObject{
	
	private:
	
		static std::list<MemoryManagedObject *> liveObjects;
		static std::list<MemoryManagedObject *> deadObjects;
		long referenceCounter;
		
	protected:
	
		MemoryManagedObject();
		virtual ~MemoryManagedObject();
		
	public:
		
		void addReference();
		void release();
		
		static void collectGarbage();
		static void collectRemainingObjects(bool EmitWarnings=false);
		virtual unsigned long size()=0;
	
};

#define AUTO_SIZE unsigned long size(){return sizeof(*this);}

template<class T>
class MemoryManagedPointer{
	
	protected:
		T* obj;
	public:
	MemoryManagedPointer(){obj=0;}
	MemoryManagedPointer(T *o){obj=0; *this=o;}
	MemoryManagedPointer(const MemoryManagedPointer<T> &p){obj=0; *this=p;}

	~MemoryManagedPointer(){if(obj)obj->release();}

	inline void operator =(const MemoryManagedPointer<T> &p){
		if(obj)obj->release();
		obj=p.obj;
		if(obj)obj->addReference();
	}
	
	inline void operator =(T* o){
		if(obj)obj->release();
		obj=o;
		if(obj)obj->addReference();
	}

	inline T& operator *() const{
		assert(obj!=0 && "Tried to * a NULL smart pointer");
		return *obj;
	}

	inline T* operator ->() const{
		assert(obj!=0 && "Tried to -> on a NULL smart pointer");
		return obj;
	}

	inline operator T*() const{
		return obj;
	}

	inline bool operator !(){return !(obj);}

	inline bool isValid() const
	{return (obj!=0);}

	inline bool operator ==(const MemoryManagedPointer<T> &p) const 
	{
		return (obj==p.obj);
	}
	inline bool operator ==(const T* o) const
	{
		return (obj==o);
	}
};

template<class T, int i>
class MemoryManagedBlob : public MemoryManagedObject{
	
	protected:
	T buffer[i];
	public:
	inline T& operator [](int index){assert(index<i); return buffer[index];}
	inline operator T*(){return buffer;}
	AUTO_SIZE;
};

template<class T>
class MemoryManagedDynamicBlob : public MemoryManagedObject{
	
	protected:
		unsigned long dataSize;
		T *buffer;
		public:
		inline T& operator [](int index){assert(index<dataSize); return buffer[index];}
		inline operator T*(){return buffer;}
		MemoryManagedDynamicBlob(unsigned long size){dataSize=size; buffer=new T[size]; }
		~MemoryManagedDynamicBlob(){if(buffer)delete[] buffer;}
		unsigned long size(){return dataSize*sizeof(T) + sizeof(this); }
		unsigned long blobsize(){return dataSize;}
};

#endif /*MEMORYMANAGEDOBJECT_H_*/
