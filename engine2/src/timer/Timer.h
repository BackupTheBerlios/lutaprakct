#ifndef _TIMER_H_
#define _TIMER_H_

#include "../util/patterns/Singleton.h"

/*classe que mede o tempo entre os frames e o FPS*/
class Timer {
	
public:

	Timer();
	virtual ~Timer(){};

	float getFPS(){ return fps; }
	float getElapsedTime(){ return elapsedTime; }
	unsigned long getCurrentTime() {return currentTime; }
	
	void update();
	void stop( ) { };
	bool initialize( );

private:

	unsigned long lastTime;
	unsigned long currentTime;
	
	float elapsedTime;
	float fps;
};

typedef Singleton<Timer> TIMER;

#endif //_TIMER_H_
