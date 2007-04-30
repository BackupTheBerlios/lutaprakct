#ifndef SKYBOXCUBE_H_
#define SKYBOXCUBE_H_

#include "../../../util/glhelper/texture.h"

/* essa versão do skybox desenha um cubo gigante sobre a cena com uma
 * textura em cada face. nao eh mto aconselhavel de utiliza-la
 */

class SkyboxCube{

	public:
	
		SkyboxCube(){ negx = negy = negz = posx = posy = posz = NULL;}
		~SkyboxCube(){};
		SkyboxCube(char* filename){ negx = negy = negz = posx = posy = posz = NULL; initialize(filename); };
		
		bool initialize(char* filename);
		
		void draw();
		
	private:
	
		Texture* negx;
		Texture* negy;
		Texture* negz;
		Texture* posx;
		Texture* posy;
		Texture* posz;
	
};

#endif /*SKYBOXCUBE_H_*/
