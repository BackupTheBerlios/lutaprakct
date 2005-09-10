#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../math/algebra.h"

/** Nao foi criado interface nem factory para a camera. essa camera atual eh muito simples
 * e usa quaternion, nao faz sentido criar outro modelo de camera (vetorial por exemplo) e criar a
 * factory pra decidir qual deve ser instanciada, ja que quaternion eh a melhor solucao.
 * se um cliente quiser criar efeitos especiais de camera use composicao (de preferencia) ou heranca
 */
 /** TODO rotatearound e positioncamera ?
  */
 
class camera {
 	
public:

	camera();
	~camera();
	void rotate(float angle, vec3& axis);
	void move(float x, vec3& axis);
 	void update(float time);
 	
private:

	float time;
    mat4 modelview;
 	
};

#endif //_CAMERA_H_
