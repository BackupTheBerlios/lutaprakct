#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../../../util/math/algebra.h"
#include "../../events/eventhandler.h"
#include "../../../util/patterns/singleton.h"

/** Nao foi criado interface nem factory para a camera. essa camera atual eh muito simples
 * e usa quaternion, nao faz sentido criar outro modelo de camera (vetorial por exemplo) e criar a
 * factory pra decidir qual deve ser instanciada, ja que quaternion eh a melhor solucao.
 * se um cliente quiser criar efeitos especiais de camera use composicao (de preferencia) ou heranca
 */
 /** TODO rotatearound e positioncamera ?
  */
 
class Camera : public eventHandler {
 	
public:

	Camera();
	~Camera();
	void initialize();
	void rotate(float angle, vec3 axis);
	void move(float x, vec3 axis);
 	void update(float time);
 	
 	vec3 getPosition();
 	
 	void handleEvent(const event &e);
 	
private:

    float velocity, velocityRotate;
	float time;
    mat4 modelview;
 	
};

typedef singleton<Camera> CAMERA;

#endif //_CAMERA_H_
