#ifndef ENGINE_H_
#define ENGINE_H_

class Engine{
	
	public:
	
		Engine();
		~Engine();
		
		bool initialize();
		
		void mainLoop();
		
		bool isRunning();
		void stop();
		
	private:
	
		bool running;
}; 

#endif /*ENGINE_H_*/
