#ifndef SKYBOX_H_
#define SKYBOX_H_

#include "../../../util/glhelper/texture.h"

class Skybox{

	public:
	
		Skybox(){ cube = NULL;}
		~Skybox(){};
		Skybox(char* filename){ cube = NULL; initialize(filename); };
		
		bool initialize(char* filename);
		
		void draw();
		
	private:
	
		texture* cube;
	
};

#endif /*SKYBOX_H_*/
