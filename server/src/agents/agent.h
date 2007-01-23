#ifndef AGENT_H_
#define AGENT_H_

/* essa e apenas a interface basica para as outras arquiteturas de agentes. todo
 * outro agente implementa essa interface
 * */
 
class Agent{
	
	public:
	
		Agent(){};
		virtual ~Agent(){};
		
		virtual bool initialize(char* filename) = 0; //aloca memoria e inicializa os scripts e variaveis
		virtual void shutdown() = 0; //desaloca memoria e finaliza o agent
		virtual void run() = 0; //main loop do agente
		virtual void beforeRun() = 0; 
		virtual void afterRun() = 0; 
		
		void stop(){ running = false; }; //pausa a execucao do agente
		void start() { running = true; };
 		bool isRunning(){ return running; };
 	
 		void* specificAgentData;
 	
 	private:
 		bool running;
 	
};


#endif /*AGENT_H_*/
