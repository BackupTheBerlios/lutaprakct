#ifndef _TIMER_H_
#define _TIMER_H_


#include "../core/task.h"

/*classe que mede o tempo entre os frames e o FPS*/
class Timer : public Task {
	
public:
	Timer();
	virtual ~Timer(){};

	float getFPS(){ return fps; }
	float getElapsedTime(){ return elapsedTime; }
	
	void  update();
	void stop() { }; //sem stop
	bool start();

	AUTO_SIZE;

private:

	unsigned long lastTime;
	unsigned long currentTime;
	
	float elapsedTime;
	float fps;
};

#endif //_TIMER_H_
