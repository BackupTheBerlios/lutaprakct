#ifndef SKYDOME_H_
#define SKYDOME_H_

#include <string>

#include "../../../util/math/algebra.h"
#include "../../material/textures/texturemanager.h"
#include "../../shaders/cloudShader.h"

class Skydome{
	
public:

	Skydome();
	Skydome(std::string filename, int sides, int slides, float radius, float dampening );
	~Skydome();

	void load(std::string filename, int sides, int slides, float radius, float dampening );
	void draw();
	
	int getSlices(){ return slices; };
	int getSide(){ return sides; };
	float getRadius(){ return radius; };
	float getDampening(){ return dampening; };
	
	void setSlices(int slices){ this->slices = slices; };
	void setSides(int sides){ this->sides = sides; };
	void setRadius(float radius){ this->radius = radius; };
	void setDampening(float dampening){ this->dampening = dampening; };


private:

	int slices, sides;
	float radius, dampening;
	
	vec3* vertices;
	vec2* texcoords;
	unsigned short* indices;
	
	texture* skytexture;
	cloudShader* clouds;
	GLuint texNoiseId;
};


#endif /*SKYDOME_H_*/
