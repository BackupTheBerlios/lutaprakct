#ifndef LAYER_H_
#define LAYER_H_

#include "subsumptionAgentData.h"

class Layer{

	public:
		Layer();
		virtual ~Layer();
	
		virtual void run(SubsumptionAgentData* data, void* auxiliarData) = 0;
		int getId();
		void setId(int id);
		
		void subsume(SubsumptionAgentData* data);
		void endSubsume(SubsumptionAgentData* data);
	
	private:
		int id;
	
};

#endif /*LAYER_H_*/
