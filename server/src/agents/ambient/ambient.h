#ifndef AMBIENT_H_
#define AMBIENT_H_

#include "../agent.h"
#include <list>

template <class T>
class Ambient : public Agent{
	
	public:
		Ambient();
		virtual ~Ambient();
		
		virtual bool initialize(char* filename) = 0;
		virtual void shutdown() = 0;
		virtual void run() = 0;
		
		std::list<T>* getAgents();
		
		void addAgent(T agent);
		
	private:
		std::list<T> agents; //agentes que estao no ambiente
};

template <class T>
void Ambient< T >::addAgent(T agent){
		agents.push_back(agent);
}

template <class T>
Ambient< T >::Ambient(){
}

template <class T>
Ambient< T >::~Ambient(){
}

template <class T>
std::list< T >* Ambient< T >::getAgents(){
	
	if (agents.empty()) 
		return NULL; 
	return &agents;
	
};

#endif /*AMBIENT_H_*/
