#ifndef LIGHT_H_
#define LIGHT_H_

#include <dom/domLight.h>
#include <dom/domTargetableFloat3.h>
#include <dae.h>
enum LightType { AMBIENT, POINT, DIRECTIONAL, SPOT };

class Light {
public:
	Light(domLight* lightTag);

	float r, g, b;
	float fallOffAngle;
	float fallOfExponent;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	
	LightType lType;
};

#endif /*LIGHT_H_*/
