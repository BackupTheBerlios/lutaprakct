
#include "QuatCamera.h"
#include <GL/gl.h>
#include <iostream>

void QuatCamera::handleEvent(const event &e){


	switch (e.type){
		case E_KEY_UP:         pivot.moveRelativeAxisN(1.0); break;
	    case E_KEY_DOWN:       pivot.moveRelativeAxisN(-1.0); break;
	    case E_KEY_W:		   pivot.moveRelativeAxisV(1.0);; break;
	    case E_KEY_S:		   pivot.moveRelativeAxisV(-1.0);; break;
	    case E_KEY_LEFT:       pivot.moveRelativeAxisU(1.0); break;
	    case E_KEY_RIGHT:      pivot.moveRelativeAxisU(-1.0); break;
	    
	    case E_MOUSE_POSITION: 	{
		    						if ( (e.arg1 == 400) && (e.arg2 == 300) )
		    							return;
		    						float deltax = (e.arg1 - 400)/800.0;
		    						float deltay = (e.arg2 - 300)/600.0;
		    						  
		    						pivot.rotateRelativeAxisU(-deltay);
		    						//pivot.rotateRelativeAxisV(deltay);
		    						pivot.rotateRelativeAxis(0.0, 1.0, 0.0, -deltax);
		    						break;
	    						}
	}	
	
}

void QuatCamera::setupViewMatrix(){
	
	Vector<float,3> P;
	pivot.getPosition(P);
	// retrieve camera rotation quaternion...
	Quaternion<float> R;
	pivot.getRotation(R);
	// retrieve rotation vectors U, V and N from the quaternion...
	Vector<float,3> U;
	Vector<float,3> V;
	Vector<float,3> N;
	R.toMatrix(U[0], U[1], U[2], V[0], V[1], V[2], N[0], N[1], N[2]);
	// manually build the view matrix...
	
	float M [16];
	M[ 0] = U[0];
	M[ 4] = U[1];
	M[ 8] = U[2];
	M[ 1] = V[0];
	M[ 5] = V[1];
	M[ 9] = V[2];
	M[ 2] = N[0];
	M[ 6] = N[1];
	M[10] = N[2];
	M[12] = P*U;
	M[13] = P*V;
	M[14] = P*N;
	M[ 3] = 0.0f;
	M[ 7] = 0.0f;
	M[11] = 0.0f;
	M[15] = 1.0f;
	// load the builded view matrix as the opengl view matrix...
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(M);
	
}
