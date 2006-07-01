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

	void setPosition(float x, float y, float z,
                     float xv, float yv, float zv,
                     float xu, float yu, float zu);

	void move(float direction);
	void update(float xDir, float yDir,
                        float zDir, float dir);
	void strafe(float direction);
	void calculateStrafe();
	void rotate(float AngleDir, float xSpeed,
                        float ySpeed, float zSpeed);
	void rotateByMouse(int mousePosX, int mousePosY,
                         int midX, int midY);

 	void handleEvent(const event &e);

	float xPos, yPos, zPos;                         
	float xView, yView, zView;                      
	float xUp, yUp, zUp;                            
	float xStrafe, yStrafe, zStrafe;                
	float currentRotationAngle;                     
 	
};

typedef singleton<Camera> CAMERA;

#endif //_CAMERA_H_
