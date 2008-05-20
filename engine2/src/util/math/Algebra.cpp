#include "Algebra.h"
#include <cmath>

double lerp(double a, double b, double x){
	return a*(1-x) + b*x;	
}

double cosineInterpolate(double a, double b, double x){
	double ft = x * 3.1415927;
	double f = (1 - cos(ft)) * .5;

	return  a*(1-f) + b*f;
}

double cubicInterpolate(double v0, double v1, double v2, double v3, double x){
	double P = (v3 - v2) - (v0 - v1);
	double Q = (v0 - v1) - P;
	double R = v2 - v0;
	double S = v1;

	return P*pow(x, 3) + Q*pow(x, 2) + R*x + S;
}
