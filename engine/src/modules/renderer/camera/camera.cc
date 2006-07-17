#include "camera.h"
#include <cmath>
#include <GL/gl.h>

#include <iostream>


Camera::Camera(){
	xPos = yPos = zPos = 0;
	xView = yView = zView = 0;
	xUp = yUp = zUp = 0;
	xStrafe = yStrafe = zStrafe = 0;
}


void Camera::setPosition(float x, float y, float z,
                        float xv, float yv, float zv,
                        float xu, float yu, float zu){
	xPos = x;   yPos = y;   zPos = z;
	xView = xv; yView = yv; zView = zv;
	xUp = xu;   yUp = yu;   zUp = zu;
}


void Camera::move(float space){
	
	float xLookDirection = 0, yLookDirection = 0, zLookDirection = 0;

	//acha o vetor direcao
	xLookDirection = xView - xPos;
	yLookDirection = yView - yPos;
	zLookDirection = zView - zPos;

	//normaliza
	float dp = 1 /(float)sqrt(xLookDirection * xLookDirection + yLookDirection * yLookDirection +
                             zLookDirection * zLookDirection);
	xLookDirection *= dp;
	yLookDirection *= dp;
	zLookDirection *= dp;

	update(xLookDirection, yLookDirection, zLookDirection, space);
}


void Camera::update(float xDir, float yDir, float zDir, float space){
	
	xPos += xDir * space;
	yPos += yDir * space;
	zPos += zDir * space;

	xView += xDir * space;
	yView += yDir * space;
	zView += zDir * space;
}


void Camera::strafe(float space){
	
   calculateStrafe();
   update(xStrafe, yStrafe, zStrafe, space);
}


void Camera::calculateStrafe(){
	
	float xDir = 0, yDir = 0, zDir = 0;
	float xCross = 0, yCross = 0, zCross = 0;

	xDir = xView - xPos;
	yDir = yView - yPos;
	zDir = zView - zPos;

	float dp = 1 /(float)sqrt(xDir * xDir + yDir * yDir + zDir * zDir);
	xDir *= dp;
	yDir *= dp;
	zDir *= dp;

	//faz o cross product entre o vetor Up e o Direction. Com isso pegamos o vetor 
	// perpendicular, que no caso esta no eixo x.

	xCross = (yDir * zUp) - (zDir * yUp);
	yCross = (zDir * xUp) - (xDir * zUp);
	zCross = (xDir * yUp) - (yDir * xUp);

	xStrafe = xCross;
	yStrafe = yCross;
	zStrafe = zCross;
}


void Camera::rotate(float AngleDir, float xSpeed, float ySpeed, float zSpeed){
	
	float xNewLookDirection = 0, yNewLookDirection = 0, zNewLookDirection = 0;
	float xLookDirection = 0, yLookDirection = 0, zLookDirection = 0;
	float CosineAngle = 0, SineAngle = 0;

	CosineAngle = (float)cos(AngleDir);
	SineAngle = (float)sin(AngleDir);

	xLookDirection = xView - xPos;
	yLookDirection = yView - yPos;
	zLookDirection = zView - zPos;

	float dp = 1 /(float)sqrt(xLookDirection * xLookDirection + yLookDirection * yLookDirection +
                             zLookDirection * zLookDirection);
	xLookDirection *= dp;
	yLookDirection *= dp;
	zLookDirection *= dp;

	// Calculate the new X position.
	xNewLookDirection = (CosineAngle + (1 - CosineAngle) * xSpeed) * xLookDirection;
	xNewLookDirection += ((1 - CosineAngle) * xSpeed * ySpeed - zSpeed * SineAngle)* yLookDirection;
	xNewLookDirection += ((1 - CosineAngle) * xSpeed * zSpeed + ySpeed * SineAngle) * zLookDirection;

	// Calculate the new Y position.
	yNewLookDirection = ((1 - CosineAngle) * xSpeed * ySpeed + zSpeed * SineAngle) * xLookDirection;
	yNewLookDirection += (CosineAngle + (1 - CosineAngle) * ySpeed) * yLookDirection;
	yNewLookDirection += ((1 - CosineAngle) * ySpeed * zSpeed - xSpeed * SineAngle) * zLookDirection;

	// Calculate the new Z position.
	zNewLookDirection = ((1 - CosineAngle) * xSpeed * zSpeed - ySpeed * SineAngle) * xLookDirection;
	zNewLookDirection += ((1 - CosineAngle) * ySpeed * zSpeed + xSpeed * SineAngle) * yLookDirection;
	zNewLookDirection += (CosineAngle + (1 - CosineAngle) * zSpeed) * zLookDirection;


	// Last we add the new rotations to the old view to correctly rotate the camera.
	xView = xPos + xNewLookDirection;
	yView = yPos + yNewLookDirection;
	zView = zPos + zNewLookDirection;
}


void Camera::rotateByMouse(int mousePosX, int mousePosY, int midX, int midY){

	
	float yDirection = 0.0f;         // Direction angle.
	float yRotation = 0.0f;          // Rotation angle.

	//se o mouse nao se moveu, retorna
	if((mousePosX == midX) && (mousePosY == midY)) 
		return;

	// pega a direcao que se moveu e divide por 1000.0
	// TODO esse 1000.0 é a sensibilidade do mouse
	yDirection = (float)((midX - mousePosX)) / 1000.0f;		
	yRotation = (float)((midY - mousePosY)) / 1000.0f;		

	currentRotationAngle -= yRotation;  
	// limite da camera para cima
	if(currentRotationAngle > 1.0f){
		currentRotationAngle = 1.0f;
		return;
	}

	// limite da camera pra baixo
	if(currentRotationAngle < -1.0f){
		currentRotationAngle = -1.0f;
		return;
	}

   //a partir daqui pega-se o vetor perpendicular ao view e o up
	float xAxis = 0, yAxis = 0, zAxis = 0;
	float xDir = 0, yDir = 0, zDir = 0;

   //Pega o vetor direcao
	xDir = xView - xPos;
	yDir = yView - yPos;
	zDir = zView - zPos;

   // cross entre direcao e up
	xAxis = (yDir * zUp) - (zDir * yUp);
	yAxis = (zDir * xUp) - (xDir * zUp);
	zAxis = (xDir * yUp) - (yDir * xUp);

   //normaliza
	float len = 1 /(float)sqrt(xAxis * xAxis + yAxis * yAxis + zAxis * zAxis);
	xAxis *= len;
	yAxis *= len;
	zAxis *= len;

   // rotaciona
	rotate(yRotation, xAxis, yAxis, zAxis);
	rotate(yDirection, 0, 1, 0);
}

void Camera::handleEvent(const event &e){

	switch (e.type){
		//case E_MOUSE_ROTATE_X: rotate(e.arg1, vec3(0.0, 1.0, 0.0)); break;
		//case E_MOUSE_ROTATE_Y: rotate(e.arg1, vec3(1.0, 0.0, 0.0)); break;
		case E_KEY_UP:         move(0.1); break;
	    case E_KEY_DOWN:       move(-0.1); break;
	    case E_KEY_LEFT:       strafe(-0.1); break;
	    case E_KEY_RIGHT:      strafe(0.1); break;
	}	
	
}
