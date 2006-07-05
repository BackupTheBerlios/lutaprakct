
#include<GL/gl.h>
#include<GL/glu.h>
#include <cmath>
#include "skydome.h"
#include "../../../util/noise/noisetexture.h"

#include <iostream>

const char* cloudVertexSource = 
"varying vec3  MCposition; 												\n"
"float Scale = 1.0;														\n"
"void main(){															\n"
"	vec3 ECposition = vec3(gl_ModelViewMatrix * gl_Vertex);				\n"
"   MCposition      = vec3(gl_Vertex) * Scale;							\n"
"   gl_Position     = ftransform();										\n"
"}																		\n\0";

const char* cloudFragmentSource =
"varying vec3  MCposition;																			\n"
"uniform sampler3D Noise;																			\n"
"vec3 SkyColor = vec3(0.0, 0.0, 0.8);																\n"
"vec3 CloudColor = vec3(0.8, 0.8, 0.8);																\n"
"void main(){																						\n"
"    vec4  noisevec  = texture3D(Noise, MCposition);												\n"
"    float intensity = (noisevec[0] + noisevec[1] + noisevec[2] + noisevec[3] + 0.03125) * 1.5;		\n"
"    vec3 color   = mix(SkyColor, CloudColor, intensity) * 1.0;										\n"
"    gl_FragColor = vec4(color, 1.0);																\n"
"}																									\n\0";

Skydome::Skydome(){
	vertices = NULL;
	indices = NULL;
}

Skydome::Skydome(std::string filename, int sides, int slices,  float radius, float dampening = 0){
	vertices = NULL;
	indices = NULL;
	load(filename, sides, slices, radius, dampening);
}

Skydome::~Skydome(){
}

void Skydome::load(std::string filename, int sides, int slices, float radius, float dampening = 0){
	this->sides = sides;
	this->slices = slices;
	this->radius = radius;
	this->dampening = dampening;
	
	vertices = new vec3[ (slices+1) * (sides + 1) ];
	texcoords = new vec2[(slices +1) * (sides + 1)];
		
	//calcula delta Theta
	float polyAngle = two_pi / sides; 
	float angle;
	float vx, vy, vz;
	for (int j = 0; j <= slices; j++){
		//calcula delta Phi
		angle = j * ( half_pi / slices );
		
		for (int i = 0; i <= sides; i ++){
			
			//calcula as coordenadas cartesianas
			vx = cos( i * polyAngle) * cos (angle);
			vy = dampening * sin(angle);
			vz = sin( i * polyAngle) * cos(angle);
			
			vertices[j * (sides + 1) + i].x = vx * radius;
			vertices[j * (sides + 1) + i].y = vy * radius;
			vertices[j * (sides + 1) + i].z = vz * radius;
			
			texcoords[j * (sides + 1 ) + i].x = (float)(i) / (float)(sides);
			texcoords[j * (sides + 1 ) + i].y = (float)(j) / (float)(slices);
		}
	}
	
	indices = new unsigned short[slices * (sides + 1) * 2];
	
	int ind = 0;
	for (int j = 1; j <= slices; j++){
		for(int i = 0; i <= sides; i++){
			indices[ind++] = j * (sides + 1) + i;
			indices[ind++] = (j - 1) * (sides + 1) + i;
		}
	}

	skytexture = TEXTUREMANAGER::getInstance().load((char*)filename.c_str(), texture::TEXTURE_2D, texture::RGB, texture::RGB8, texture::ANISOTROPIC_4);
	texNoiseId = init3DNoiseTexture();
	clouds = new cloudShader( cloudVertexSource, cloudFragmentSource );
	clouds->setInitialParameters();
}


void Skydome::draw(){
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
	
	//skytexture->enable();
	//skytexture->bind();
	glEnable(GL_TEXTURE_3D);
	glBindTexture(GL_TEXTURE_3D, texNoiseId);
	clouds->bind();
	for(int i = 0; i < slices; i++)
		glDrawElements(GL_TRIANGLE_STRIP, (sides + 1) * 2, GL_UNSIGNED_SHORT, &indices[i * (sides + 1) * 2]);
	
	clouds->unbind();
	//skytexture->disable();
	glDisable(GL_TEXTURE_3D);
	clouds->unbind();
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

