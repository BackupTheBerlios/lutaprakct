#include "Light.h"
#include <dom/domLight.h>

Light::Light(domLight* lightTag)
{
	domLight::domTechnique_common* techCommon = lightTag->getTechnique_common();
	if (techCommon == NULL)
		//fudeu, faz o que?
	
	domLight::domTechnique_common::domAmbient* ambient_Light = techCommon->getAmbient();
	domLight::domTechnique_common::domDirectional* directional_Light = techCommon->getDirectional();
	domLight::domTechnique_common::domPoint* point_Light = techCommon->getPoint();
	domLight::domTechnique_common::domSpot* spot_Light = techCommon->getSpot(); 
	
	//a luz só pode ser ambient ou direcitona, ou spot, ou point? não pode ter os 2 elementos ao mesmo tempo?
	if (ambient_Light){
		lType = AMBIENT;
		//domFloat3 &color = ambientElement->getColor()->getValue();
	} else if (directional_Light) {
		lType = DIRECTIONAL;
	} else if (point_Light){
		lType = POINT;
	 }else if (spot_Light) {
		lType = SPOT;
	 }
	//lightTag->getTechnique_array().getCount()
	//for(size_t i = 0; i < lightTag->getTechnique_array()->getCount(); i++) {
	//}
}
