#ifndef _TIMER_H_
#define _TIMER_H_

/*classe que mede o tempo entre os frames e o FPS*/

class timer {
	
public:
	timer();
	~timer(){};

	float getFPS(){ return fps; }
	float getSPF(){ return spf; }
	void  update();

private:
	float fps;
	float spf;
};

#endif //_TIMER_H_
