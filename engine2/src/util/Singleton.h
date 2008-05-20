#ifndef _SNGLETON_H_
#define _SNGLETON_H_

/** um simples template pra singleton
 * uso: typedef singleton<classe> nomeTipo;
 * nomeTipo::getInstance().foo();
 */
 
 
template <class T>
class Singleton{
public:
	static T& getInstance() {
		static T instance;
		return instance;
	}
private:
	Singleton();
	~Singleton();
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);
};

#endif //_SNGLETON_H_
