#ifndef SKYCOLOR_H_
#define SKYCOLOR_H_

#include "../../../util/math/algebra.h"

class SkyColor{
	
public: 
	
	SkyColor();
	
	void getVertexColor(float Theta, float Phi, float SunPhi, vec4* color);
	void setInfo(float SunTheta, float Turbidity);


private:
	
	void toRGBA(float x, float y, float Y, vec4* rgb);
	float angle(float theta1, float phi1, float theta2, float phi2);
	
	inline float perezFunction_x(float, float, float);
	inline float perezFunction_y(float, float, float);
	inline float perezFunction_Y(float, float, float);

	float Ax, Bx, Cx, Dx, Ex;
	float Ay, By, Cy, Dy, Ey;
	float AY, BY, CY, DY, EY;
	
	float T, suntheta, T2, suntheta3, suntheta2;	
	float xz, yz, Yz;
	float cosSTheta;
};


#endif /*SKYCOLOR_H_*/
