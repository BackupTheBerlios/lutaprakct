
#include<GL/gl.h>
#include<GL/glu.h>
#include <cmath>
#include "skydome.h"

#include <iostream>

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
	
}


void Skydome::draw(){
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
	
	skytexture->enable();
	skytexture->bind();
	
	for(int i = 0; i < slices; i++)
		glDrawElements(GL_TRIANGLE_STRIP, (sides + 1) * 2, GL_UNSIGNED_SHORT, &indices[i * (sides + 1) * 2]);
	
	skytexture->disable();
	glDisable(GL_TEXTURE_2D);
	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

