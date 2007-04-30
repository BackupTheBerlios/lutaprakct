#ifndef SKYDOME_H_
#define SKYDOME_H_

#include <string>
#include "skyColor.h"
#include "../../../util/math/algebra.h"
#include "../../material/textures/texturemanager.h"
#include "../../shaders/glslshaders/cloudShader.h"

/*se usar o flag ANIMATED_CLOUDS deve-se ativar o flag COLORED_SKY tambem. porque o shader
 * que anima as nuvens pega a cor por vertice do skydome, entao as cores precisam ser
 * calculadas e enviadas para o shader. */
enum {
	
	ANIMATED_CLOUDS = 1 << 1,
	STATIC_CLOUDS = 1 << 2,
	COLORED_SKY = 1 << 3,
	SKY_ELEMENTS = 1 << 4
};

class Skydome{
	
public:

	Skydome();
	Skydome(std::string filename, int sides, int slides, float radius, int flags, float dampening );
	~Skydome();

	void load(std::string filename, int sides, int slides, float radius, int flags, float dampening );
	void update(float deltatime);
	void draw();
	void drawElements(bool initial);
	
	int getSlices(){ return slices; };
	int getSide(){ return sides; };
	float getRadius(){ return radius; };
	float getDampening(){ return dampening; };
	
	vec4 getHorizonColor();
	
	void setSlices(int slices){ this->slices = slices; };
	void setSides(int sides){ this->sides = sides; };
	void setRadius(float radius){ this->radius = radius; };
	void setDampening(float dampening){ this->dampening = dampening; };
	
	void setCoordinates(float Lat, float Long, float Time, float Day){
			latitude = degtorad(Lat);
			longitude = degtorad(Long);
			julianDay = Day;
			timeOfDay = Time * 3600.0f;
	};

private:

	int slices, sides, flags;
	float radius, dampening;
	float timeOfDay, julianDay, latitude, longitude;
	
	SkyColor skyColor;
	float sunTheta, sunPhi;
	float moonTheta, moonPhi;
	vec3* stars;
	vec4* starColors;
	int starsNum;
	
	vec3* vertices;
	vec2* texcoords;
	vec4* colors;
	unsigned short* indices;
	
	CloudShader* cshader;
	Texture* nuvem;
	Texture* skytexture;
	Texture* moon;
	Texture* sun;
};


#endif /*SKYDOME_H_*/
