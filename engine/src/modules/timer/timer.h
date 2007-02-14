#ifndef _TIMER_H_
#define _TIMER_H_


#include "../core/task.h"
#include "../../util/patterns/singleton.h"

/*classe que mede o tempo entre os frames e o FPS*/
class Timer : public Task {
	
public:
	Timer();
	virtual ~Timer(){};

	float getFPS(){ return fps; }
	float getElapsedTime(){ return elapsedTime; }
	unsigned long getCurrentTime() {return currentTime; }
	
	void  update(void* data );
	void stop(void* data ) { }; //sem stop
	bool start(void* data );

	AUTO_SIZE;

private:

	unsigned long lastTime;
	unsigned long currentTime;
	
	float elapsedTime;
	float fps;
};

typedef singleton<Timer> TIMER;

#endif //_TIMER_H_
