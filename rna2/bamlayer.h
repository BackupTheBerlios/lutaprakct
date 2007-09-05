#ifndef BAMLAYER_H_
#define BAMLAYER_H_


class BAMLayer { 
public: 
     int               totalNeurons; //numero de neuronios da camada
     int               totalNextNeurons;  //numero de neuronios da camada inferior
     int               totalPrevNeurons; //numero de neuronios da camada superior
     
     int**          weights; 
     int*           neuronValues; 
     
     BAMLayer*     prevLayer; 
     BAMLayer*     nextLayer; 
     BAMLayer(); 
     
     void     initialize(int NumNodes, BAMLayer* parent, BAMLayer* child); 
     void     shutdown(void); 
     void     randomizeWeights(void); 
     void     adjustWeights(void); 
     void     calculateNeuronValues(void); 
};


#endif /*BAMLAYER_H_*/
