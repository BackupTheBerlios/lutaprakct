#ifndef SKYBOX_H_
#define SKYBOX_H_

#include "../../../util/glhelper/texture.h"
#include <string>

/* essa versao do sky box nao escreve no depthbuffer e usa cubemapping
 * use essa versao ao inves da skyboxcube
 * */

class Skybox{

	public:
	
		Skybox(){ cube = NULL;}
		~Skybox(){};
		Skybox(std::string filename, float size, int followcamera, int enabled){ cube = NULL; initialize(filename, size, followcamera, enabled); };
		
		bool initialize(std::string& filename, float size, int followcamera, int enabled);
		
		void draw();
		
		int isEnabled() { return enabled;}; 
		
	private:
	
		Texture* cube;
		float size;
		int followcamera;
		int enabled;
};

#endif /*SKYBOX_H_*/
