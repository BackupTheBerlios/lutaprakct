#include "neuralnetwork.h"
#include "somNetwork.h"
#include <iostream>
#include <fstream>
#include <vector>
neuralNetwork mlp;

double treinamentoVentilacao[10][5] = {
5.3, 4.95, 5.3, 3.55, 5.5,
4.95, 5.3, 3.55, 5.5, 5.1, 
5.3, 3.55, 5.5, 5.1, 5.86,
3.55, 5.5, 5.1, 5.86, 5.1,
5.5, 5.1, 5.86, 5.1, 3.85,
5.1, 5.86, 5.1, 3.85, 4,
5.86, 5.1, 3.85, 4, 0.1,
5.1, 3.85, 4, 0.1, 3.8,
3.85, 4, 0.1, 3.8, 3.7,
4, 0.1, 3.8, 3.7, 3.5,
};

/*double treinamentoVeiculo[21][5] = {
1.0,  	1.0,  	1.0,  	1.0,  	0.5,
0.5, 	1.0, 	1.0, 	0.6, 	0.7,
1.0, 	1.0, 	0.5, 	0.6, 	0.3,
1.0, 	0.5, 	1.0, 	0.3, 	0.4,
0.5, 	1.0, 	0.5, 	0.7, 	0.5,
0.0, 	0.0, 	0.0, 	0.2, 	0.2,
0.5, 	0.5, 	0.5, 	0.5, 	0.4,
0.0, 	1.0, 	1.0, 	0.4, 	0.9,
1.0, 	1.0, 	0.0, 	0.4, 	0.1,
1.0, 	0.0, 	1.0, 	0.2, 	0.2,
0.0, 	1.0, 	0.0, 	1.0, 	0.5,
0.0, 	0.0, 	1.0, 	0.3, 	0.8,
1.0, 	0.0, 	0.0, 	0.3, 	0.2,
0.3, 	0.4, 	0.1, 	0.5, 	0.3,
0.1, 	0.4, 	0.3, 	0.5, 	0.7,
0.0, 	0.1, 	0.2, 	0.3, 	0.9,
0.2, 	0.1, 	0.0, 	0.3, 	0.1,
0.0, 	0.3, 	0.6, 	0.5, 	0.8,
0.6, 	0.3, 	0.0, 	0.5, 	0.2,
0.2, 	0.3, 	0.4, 	0.5, 	0.9,
0.4, 	0.3, 	0.2, 	0.4, 	0.1,
};*/

float tr[980][9];
float sl[300][9];

void treinamentoVentilacaoProc(){

	mlp.initialize(4, "%d %d %d %d", 4, 4, 3, 1);
	mlp.setLearningRate(0.2);
//	mlp.setMomentum(true, 0.9);
	std::fstream erroOut("erro.txt", std::ios::out);
	
	double error = 1000;
	int c = 0;

	while ( (c < 60000) ){
		error = 0;
		c++;
		for (int i = 0; i<10; i++){
			mlp.setInput(0, treinamentoVentilacao[i][0]);
			mlp.setInput(1, treinamentoVentilacao[i][1]);
			mlp.setInput(2, treinamentoVentilacao[i][2]);
			mlp.setInput(3, treinamentoVentilacao[i][3]);
			mlp.setDesiredOutput(0, treinamentoVentilacao[i][4]);
			mlp.feedForward();
			error += mlp.calculateError();
			mlp.backPropagate();
		}
		error /= 2;
		std::cout << c << std::endl;
		erroOut << c << " " << error << std::endl;
	}
	

/*	mlp.setInput(0, sl[i][0]);
	mlp.setInput(1, sl[i][1]);
	mlp.setInput(2, sl[i][2]);
	mlp.setDesiredOutput(0, sl[i][4]);
	mlp.feedForward();	*/
	
	mlp.printStatus("status2");
}

void treinamento(){
	
	mlp.initialize(6, "%d %d %d %d %d %d", 10, 7, 5, 4, 3, 1);
	mlp.setLearningRate(0.2);
	mlp.setMomentum(true, 0.9);
	
	double error = 1;
	int c = 0;
	
	FILE* f;
	char line[200];
	f = fopen ("normalizados2.txt", "rt"); 
	if (!f)
		std::cout << "File not found." << std::endl;

	//le todo o arquivo e coloca na matriz	
	int i = 0;
	std::cout << "Lendo arquivo com dados.. ";
	while(fgets(line, 200, f) != NULL){
		//sscanf (line, "%f %f %f %f %f %f %f %f %f %f %f", &tr[i][0], &tr[i][1],
		//&tr[i][2], &tr[i][3], &tr[i][4], &tr[i][5], &tr[i][6], &tr[i][7], &tr[i][8], &tr[i][9], &tr[i][10]);
		sscanf (line, "%f %f %f %f %f %f %f %f %f", &tr[i][0], &tr[i][1],
		&tr[i][2], &tr[i][3], &tr[i][4], &tr[i][5], &tr[i][6], &tr[i][7], &tr[i][8]);
		i++;
	}
	std::cout << "Pronto." << std::endl;
	
	int j = 0;
	i = 0;
	std::cout << "Escolhendo valores para treinamento...";
	std::fstream erroOut("erro.txt", std::ios::out);
	while (j < 60){
			sl[j][0] = tr[i][0];
			sl[j][1] = tr[i][1];
			sl[j][2] = tr[i][2];
			sl[j][3] = tr[i][3];
			sl[j][4] = tr[i][4];
			sl[j][5] = tr[i][5];
			sl[j][6] = tr[i][6];
			sl[j][7] = tr[i][7];
			sl[j][8] = tr[i][8];
			//sl[j][9] = tr[i][9];
			//sl[j][10] = tr[i][10];
			j++;
			i+=1;
	}
	std::cout << "Pronto." << std::endl;
	
	std::cout << "Iniciando treinamento da rede. " << std::endl;
	while ( (error > 0.001) && (c < 60000) ){
		error = 0;
		c++;
		for (int i = 0; i<60; i++){
			mlp.setInput(0, sl[i][0]);
			mlp.setInput(1, sl[i][1]);
			mlp.setInput(2, sl[i][2]);
			mlp.setInput(3, sl[i][3]);
			mlp.setInput(4, sl[i][4]);
			mlp.setInput(5, sl[i][5]);
			mlp.setInput(6, sl[i][6]);
			mlp.setInput(7, sl[i][7]);
			//mlp.setInput(8, sl[i][8]);
			//mlp.setInput(9, sl[i][9]);
			mlp.setDesiredOutput(0, sl[i][8]);
			mlp.feedForward();
			error += mlp.calculateError();
			
			mlp.backPropagate();
		}
		error /= 2;
		erroOut << c << " " << error << std::endl;
	}
	std::cout << "Erro Final: " << error << std::endl;
	std::cout << "Iteracoes: " << c << std::endl;
	
}

int main(){

//	treinamentoVentilacaoProc();
//	return 1;
	
/*	std::string folder = "cantos3d/";
	
	std::string config = "config.txt";
	std::string learn = "treinamento.txt";
	std::string learnError = "erroTreinamento.txt";
	std::string input = "dados.txt";
	std::string inputError = "final.txt";
	std::string status = "status.txt";
	
	if (!mlp.initialize( const_cast<char*>((folder+config).c_str()) ))
		std::cout << "Nao foi possivel criar a rede." << std::endl;
	
	mlp.learn( const_cast<char*>((folder+learn).c_str()), const_cast<char*>((folder+learnError).c_str()));
	
	mlp.setInput(const_cast<char*>((folder+input).c_str()), const_cast<char*>((folder+inputError).c_str()));
	
	mlp.printStatus(const_cast<char*>((folder+status).c_str()));*/

	SomNetwork som;
	som.initialize(40, 40, 1000, 3);
	std::vector<double> red, green, blue, yellow, orange, purple, dk_green, dk_blue;

	red.push_back(1);
	red.push_back(0);
	red.push_back(0);

	green.push_back(0);
	green.push_back(1);
	green.push_back(0);

	dk_green.push_back(0);
	dk_green.push_back(0.5);
	dk_green.push_back(0.25);

	blue.push_back(0);
	blue.push_back(0);
	blue.push_back(1);

	dk_blue.push_back(0);
	dk_blue.push_back(0);
	dk_blue.push_back(0.5);

	yellow.push_back(1);
	yellow.push_back(1);
	yellow.push_back(0.2);

	orange.push_back(1);
	orange.push_back(0.4);
	orange.push_back(0.25);

	purple.push_back(1);
	purple.push_back(0);
	purple.push_back(1);

	std::vector< std::vector<double> > TrainingSet;
	TrainingSet.push_back(red);
	TrainingSet.push_back(green);
	TrainingSet.push_back(blue);
	TrainingSet.push_back(yellow);
	TrainingSet.push_back(orange);
	TrainingSet.push_back(purple);
	TrainingSet.push_back(dk_green);
	TrainingSet.push_back(dk_blue);
  
	som.train(TrainingSet);
	std::string filename = "som2.txt";
	som.saveWeights(filename);

/*	std::cout << "Testando 10 valores aprendidos." << std::endl;
	int j = 0;
	int random;
	while (j < 10){
		random = rand()%60;
		j++;
		mlp.setInput(0, tr[random][0]);
		mlp.setInput(1, tr[random][1]);
		mlp.setInput(2, tr[random][2]);
		mlp.setInput(3, tr[random][3]);
		mlp.setInput(4, tr[random][4]);
		mlp.setInput(5, tr[random][5]);
		mlp.setInput(6, tr[random][6]);	
		mlp.setInput(7, tr[random][7]);
		//mlp.setInput(8, tr[random][8]);
		//mlp.setInput(9, tr[random][9]);
		std::cout << j << " valor desejado: " << tr[random][8] << std::endl;	
		mlp.feedForward();
		std::cout << j<<" valor obtido: " <<  mlp.getOutput(0) << std::endl;
		
		
	}
*/



	return 0;
}

