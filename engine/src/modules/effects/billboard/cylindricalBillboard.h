#ifndef CYLINDRICALBILLBOARD_H_
#define CYLINDRICALBILLBOARD_H_

#include "../../renderer/camera/camera.h"
#include "../../../util/math/algebra.h"

/* classe simples para fazer billboarding cilindrico. 
 * basta setar a posicao do objeto sempre que ela mudar
 * e chamar a função bind() antes de desenha-lo. nao
 * esquecer de salvar a matriz do opengl
 * */
 
class CylindricalBillboard{
	
	public:
	
		void bind();
		
		void setPosition(float x, float y, float z);
		void setPosition(vec3& pos);
	
	private:
	
		vec3 objectPosition;
};

#endif /*CYLINDRICALBILLBOARD_H_*/
