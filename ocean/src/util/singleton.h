#ifndef _SINGLETON_H_
#define _SINGLETON_H_

/** um simples template pra singleton
 * uso: typedef singleton<classe> nomeTipo;
 * nomeTipo::getInstance().foo();
 */
 
 
template <class T>
class singleton{
public:
	static T& getInstance() {
		static T instance;
		return instance;
	}
private:
	singleton();
	~singleton();
	singleton(singleton const&);
	singleton& operator=(singleton const&);
};


#endif //_SINGLETON_H_
