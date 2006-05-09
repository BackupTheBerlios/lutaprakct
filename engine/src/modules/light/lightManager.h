#ifndef _LIGHTMANAGER_H_
#define _LIGHTMANAGER_H_

/* Status: incompleta. 
 * funciona como o gerenciador da luz por pixel na engine, cada lightsource eh adicionado,
 * o manager cuida de suas informa?oes como posi?oes, tipo e cor da luz, e adiciona essas
 * informacoes no context dos shaders, entao  os shaders de luz sao atualizados 
 * a medida q mais luzes sao adicionadas na  engine.
 * */

class lightManager{
	
public:
	lightManager();
	~lightManager();

	void addLight();
	

private:
	
	
};

#endif //_LIGHTMANAGER_H_
