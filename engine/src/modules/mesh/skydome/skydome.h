#ifndef SKYDOME_H_
#define SKYDOME_H_

#include <string>
#include "skyColor.h"
#include "../../../util/math/algebra.h"
#include "../../material/textures/texturemanager.h"

class Skydome{
	
public:

	Skydome();
	Skydome(std::string filename, int sides, int slides, float radius, float dampening );
	~Skydome();

	void load(std::string filename, int sides, int slides, float radius, float dampening );
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

	int slices, sides;
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
	
	texture* skytexture;
	texture* moon;
	texture* sun;
};


#endif /*SKYDOME_H_*/
