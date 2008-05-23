#include "Light.h"
#include <iostream>
Light::Light(domLight* lightTag)
{
	domLight::domTechnique_common* techCommon = lightTag->getTechnique_common();
	if (techCommon == NULL)
		//fudeu, faz o que?
	
	domLight::domTechnique_common::domAmbient* zero;
	
	domLight::domTechnique_common::domAmbient* ambient_Light = techCommon->getAmbient();
	domLight::domTechnique_common::domDirectional* directional_Light = techCommon->getDirectional();
	domLight::domTechnique_common::domPoint* point_Light = techCommon->getPoint();
	domLight::domTechnique_common::domSpot* spot_Light = techCommon->getSpot();

	if (ambient_Light){
		lType = AMBIENT;
		domTargetableFloat3Ref colorTarg = ambient_Light->getColor();
		domFloat3& color = colorTarg->getValue();
		r = (float) color[0];
		g = (float) color[1];
		b = (float) color[2];
		std::cout << "Luz: " << lType << std::endl;
		std::cout << "r: " << r << "g: " << g << "b: " << b << std::endl;
	} else if (directional_Light) {
		lType = DIRECTIONAL;
		domTargetableFloat3Ref colorTarg = directional_Light->getColor();
		domFloat3& color = colorTarg->getValue();
		r = (float) color[0];
		g = (float) color[1];
		b = (float) color[2];
	} else if (point_Light){
		lType = POINT;
		domTargetableFloat3Ref colorTarg = point_Light->getColor();
		domFloat3& color = colorTarg->getValue();
		r = (float) color[0];
		g = (float) color[1];
		b = (float) color[2];
		if (point_Light->getConstant_attenuation()) {
			domTargetableFloatRef consAttenuation = point_Light->getConstant_attenuation();
			constantAttenuation = (float) consAttenuation->getValue();
		}
		if (point_Light->getLinear_attenuation()) {
			domTargetableFloatRef linAttenuation = point_Light->getLinear_attenuation();
			linearAttenuation = (float) linAttenuation->getValue();
		}
		if (point_Light->getQuadratic_attenuation()) {
			domTargetableFloatRef quadAttenuation = point_Light->getQuadratic_attenuation();
			quadraticAttenuation = (float) quadAttenuation->getValue();
		}
	 }else if (spot_Light) {
		lType = SPOT;
		domTargetableFloat3Ref colorTarg = spot_Light->getColor();
		domFloat3& color = colorTarg->getValue();
		r = (float) color[0];
		g = (float) color[1];
		b = (float) color[2];
		if (spot_Light->getConstant_attenuation()) {
			domTargetableFloatRef consAttenuation = spot_Light->getConstant_attenuation();
			constantAttenuation = (float) consAttenuation->getValue();
		}
		if (spot_Light->getLinear_attenuation()) {
			domTargetableFloatRef linAttenuation = spot_Light->getLinear_attenuation();
			linearAttenuation = linAttenuation->getValue();
		}
		if (spot_Light->getQuadratic_attenuation()) {
			domTargetableFloatRef quadAttenuation = spot_Light->getQuadratic_attenuation();
			quadraticAttenuation = quadAttenuation->getValue();
		}
	 }
}
