#ifndef ALGEBRA_H_
#define ALGEBRA_H_

#define PI (3.14159265358979323846)
//#define 2PI (2.0 * PI)
#define PI_DIV_180 (0.017453292519943296)
#define INV_PI_DIV_180 (57.2957795130823229)

#define DegToRad(x)	((x)*PI_DIV_180)
#define RadToDeg(x)	((x)*INV_PI_DIV_180)

//funcoes de interpolacao
double lerp(double a, double b, double x);
double cosineInterpolate(double a, double b, double x);
double cubicInterpolate(double v0, double v1, double v3, double v3, double x);

#endif /*ALGEBRA_H_*/
