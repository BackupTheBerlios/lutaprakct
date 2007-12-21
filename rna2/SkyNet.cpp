
#include "SkyNet.h"

bool SkyNet::initialize(){

	SkyNeuron neuron1;
	SkyNeuron neuron2;
	
	neurons.push_back(neuron1);
	neurons.push_back(neuron2);
	
	return true;
}

std::vector<SkyNeuron*> SkyNet::findWinnings(const std::vector<double>& v){

	std::vector<SkyNeuron*> winnings;
	SkyNeuron* winner1;
	SkyNeuron* winner2;
	winner1 = winner2 = NULL;
	
	double LowestDistance = 999999;
 
	for (unsigned int n = 0; n < neurons.size(); n++){
  	
		double dist = neurons[n].calculateDistance(v);

		if (dist < LowestDistance){
			LowestDistance = dist;
			winner2 = winner1;
			winner1 = &neurons[n];
		}
	}
	
	winnings.push_back(winner1);
	winnings.push_back(winner2);
	return winnings;
}

void SkyNet::initializeConnections(std::vector<SkyNeuron*>& n){

	if ( n[0]->hasConnectionWith(n[1]))
		return;
	else{ //se nao tiver uma conection, cria
		SkyNeuronConnection<SkyNeuron*>* con = new SkyNeuronConnection<SkyNeuron*>();
		con->a = n[0];
		con->b = n[1];
		n[0]->addConnection(con);
		n[1]->addConnection(con);
	}
	
}

