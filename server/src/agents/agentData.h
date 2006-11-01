#ifndef AGENTDATA_H_
#define AGENTDATA_H_

/*classe que guarda os dados internos do agente. cada arquitetura e problema
 * precisa herdar dessa classe e instancia-la no agente
 * */

class AgentData{
	
	public:
	
		AgentData(){};
		virtual ~AgentData(){};
};

#endif /*AGENTDATA_H_*/
