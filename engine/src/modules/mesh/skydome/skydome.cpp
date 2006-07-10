
#include<GL/gl.h>
#include<GL/glu.h>
#include <cmath>
#include "skydome.h"
#include "../../renderer/camera/camera.h"


const char* cloudVertexSource2 =
"//varying float intensity_sq, intensity;													\n"
"varying vec4 color; \n"
"uniform float time;																		\n"
"void main(){																			\n"
"   color = gl_Color; \n"
"   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;								\n"
"//   float tex = gl_TexCoord[0].x; \n"
"//   float tex2 = gl_TexCoord[0].y; \n"
"//   gl_TexCoord[0] = vec4( (tex + time), (tex2 + time), 0.0, 0.0); \n"
"	  gl_TexCoord[0] = vec4( (gl_Vertex.x / 1000.0) + time, gl_Vertex.z / 1000.0, 0.0, 0.0);	\n"
"//   gl_TexCoord[1] = vec4( (tex2 + time) , (tex + time), 0.0, 0.0); \n"
"//	  gl_TexCoord[1] =vec4(gl_Vertex.x / 1000.0 + time, gl_Vertex.z/1000.0 , 0.0, 0.0);	\n"
"//   intensity    = gl_Vertex.y / 1000.0;													\n"
"//   intensity    = clamp(intensity, 0.0, 1.0) / 1.8;								\n"
"//   intensity_sq = intensity * intensity;												\n"
"}																						\n\0";

const char* cloudFragmentSource2=
"//varying float intensity_sq, intensity;												\n"
"varying vec4 color; \n"
"uniform sampler2D s_texture_0;														\n"
"uniform sampler2D s_texture_1;														\n"
"vec4 horizon = vec4(0.1, 0.1, 0.8, 1.0);											\n"
"void main(){																		\n"
"   vec4 clouds_0 = texture2D(s_texture_0, gl_TexCoord[0].xy);						\n"
" //  vec4 clouds_1 = texture2D(s_texture_1, gl_TexCoord[1].xy);						\n"
"   vec4 clouds = (clouds_0 + clouds_0) * 0.4; //intensity_sq;								\n"
"//   vec4 cloud_color = vec4((1.0 - intensity) * horizon.x, (1.0 - intensity) * horizon.y, intensity * horizon.z, 0.0);	\n"
"//   vec4 cloud_color = vec4((1.0 - intensity), (1.0 - intensity) * horizon.y, intensity * horizon.z, 0.0);	\n"
"//	vec4 cloud_color = mix(gl_Color, clouds, 1.5);										\n"
"   gl_FragColor =  color + clouds; // cloud_color * (1.0 - clouds.x) + clouds;			\n"
"}																					\n\0";



Skydome::Skydome(){
	vertices = NULL;
	indices = NULL;
	colors = NULL;
	texcoords = NULL;
	stars = NULL;
	starColors = NULL;
	
}

Skydome::Skydome(std::string filename, int sides, int slices,  float radius, int flags, float dampening = 0){
	vertices = NULL;
	indices = NULL;
	colors = NULL;
	texcoords = NULL;
	stars = NULL;
	starColors = NULL;
	load(filename, sides, slices, radius, flags, dampening);
}

Skydome::~Skydome(){
	if (vertices)
		delete vertices;
	if (indices)
		delete indices;
	if (colors)
		delete colors;
	if (texcoords)
		delete texcoords;
	if (stars)
		delete stars;
	if (starColors)
		delete starColors;
}

void Skydome::load(std::string filename, int sides, int slices, float radius, int flags, float dampening = 0){
	this->sides = sides;
	this->slices = slices;
	this->radius = radius;
	this->dampening = dampening;
	this->flags = flags;
	
	vertices = new vec3[ (slices+1) * (sides + 1) ];
	if (flags &STATIC_CLOUDS)
		texcoords = new vec2[(slices +1) * (sides + 1)];
	if (flags &COLORED_SKY)
		colors = new vec4[(slices +1) * (sides + 1)];
		
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
			
			if (flags &STATIC_CLOUDS){
				texcoords[j * (sides + 1 ) + i].x = (float)(i) / (float)(sides);
				texcoords[j * (sides + 1 ) + i].y = (float)(j) / (float)(slices);
			}
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

	if (flags &STATIC_CLOUDS)
		skytexture = TEXTUREMANAGER::getInstance().load((char*)filename.c_str(), texture::TEXTURE_2D, texture::RGB, texture::RGB8, texture::ANISOTROPIC_4);
	
	if (flags &ANIMATED_CLOUDS){
		nuvem = TEXTUREMANAGER::getInstance().load("clouds.tga", texture::TEXTURE_2D, texture::RGB, texture::RGB8, 0 );
		cshader = new cloudShader(cloudVertexSource2, cloudFragmentSource2);
		cshader->setInitialParameters();
	}
	
	if (flags &SKY_ELEMENTS){
		
		sun = TEXTUREMANAGER::getInstance().load("flare0.tga", texture::TEXTURE_2D, texture::RGB, texture::RGBA8, 0);
		moon = TEXTUREMANAGER::getInstance().load("moon.tga", texture::TEXTURE_2D, texture::RGBA, texture::RGBA8, 0);
	
		starsNum = 1000;
		stars = new vec3[starsNum];
		starColors = new vec4[starsNum];
	
		float st, sp, c; //star theta, star phi
		for (int i = 0; i < starsNum; i++){
		
			st = (rand() % 90) / 180.0f * pi;
			sp = (rand() % 360) / 180.0f * pi;

			stars[i].x = cos(sp) * cos(st) * radius;
			stars[i].y = sin(st) * radius * dampening;
			stars[i].z = sin(sp) * cos(st) * radius;
		
			c = (rand() % 256) / 255.0f;

			starColors[i] = vec4(c, c, c, c);
		}
	}

	
}

vec4 Skydome::getHorizonColor(){	
	
	float ang = atan2(CAMERA::getInstance().zView, CAMERA::getInstance().xView);
	if (ang < 0) ang = 2 * pi + ang;
	int ri = (int)((ang / (2 * pi)) * sides);
	
	return vec4(colors[ri].x, colors[ri].y, colors[ri].z, 1.0f);
}

void Skydome::update(float deltatime){

	timeOfDay += deltatime;
	if (timeOfDay > 3600 * 24){
		julianDay += 1.0f;
		timeOfDay -= 3600 * 24;
	}
	
	float hour = timeOfDay / 3600.0f;
	float solarTime = hour + 0.170 * sin( 4 * pi * (julianDay - 80) / 373 ) - 0.129 * sin( 2 * pi * (julianDay - 8) / 355) + 12 * (latitude - longitude) / pi;
	float declination = 0.4093 * sin( 2 * pi * (julianDay - 81) / 368 );
	
	sunTheta = pi / 2 - asin(sin(latitude) * sin(declination) - cos(latitude) * cos(declination) * cos(pi * solarTime / 12));
	sunPhi   = atan( -cos(declination) * sin(pi * solarTime / 12) / ((cos(latitude) * cos(declination) - sin(latitude) * sin(declination) * sin(pi * solarTime / 12)))); 

	if (sunPhi < 0) sunPhi = 2 * pi + sunPhi;
	
    moonPhi = pi / 2;
    moonTheta = pi / 3;

	int ind, num;
	
	float SliceAng = (pi / 2) / slices;
	float SideAng = (pi * 2) / sides;
	
	float theta, phi;
    float turbidity = 2.0f;
	int index = 0;	
	skyColor.setInfo(sunTheta, turbidity);
	
	for (ind = 0; ind <= slices; ind++){
		for (num = 0; num <= sides; num++){
			theta = half_pi - SliceAng * ind;
			phi = num * SideAng;
			if (flags &COLORED_SKY)
				skyColor.getVertexColor(theta, phi, sunPhi, &colors[index]);
			index++;
		}
	}
	
}

void Skydome::draw(){
	
	glPushMatrix();
	
	if (flags &SKY_ELEMENTS){
		glDisable(GL_DEPTH_TEST);
		drawElements(true); 
		glEnable(GL_DEPTH_TEST);
	}
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	if (flags &STATIC_CLOUDS){
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
		skytexture->bind();
	}
	if ( flags &ANIMATED_CLOUDS){
		glActiveTextureARB(GL_TEXTURE0 + 0);
		nuvem->bind();
		cshader->bind();
	}
	if ( flags & COLORED_SKY ){
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_FLOAT, 0, &colors[0]);
	}
    
	for(int i = 0; i < slices; i++)
		glDrawElements(GL_TRIANGLE_STRIP, (sides + 1) * 2, GL_UNSIGNED_SHORT, &indices[i * (sides + 1) * 2]);
	
	if (flags &STATIC_CLOUDS){
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		skytexture->unbind();
	}
	if (flags &ANIMATED_CLOUDS){
		glActiveTextureARB(GL_TEXTURE0 + 0);
		cshader->setLoopParameters();
		cshader->unbind();
		nuvem->unbind();
	}
	if ( flags &COLORED_SKY )
		glDisableClientState(GL_COLOR_ARRAY);

	glDisableClientState(GL_VERTEX_ARRAY);
	/*reseta a cor pro default 1, 1, 1, 1 ou todos os objetos vao ficar com
	 * a ultima cor usada pelo skydome */
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
	if (flags &SKY_ELEMENTS){
		glDisable(GL_DEPTH_TEST);
		drawElements(false);  
		glEnable(GL_DEPTH_TEST);
	}
	
	glPopMatrix();
}


void Skydome::drawElements(bool initial){
	
	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
		
	vec3 vx(mat[0], mat[4], mat[8] );
	vec3 vy(mat[1], mat[5], mat[9] );
	vec3 Vertices[4];

	float SunSize = 70, MoonSize = 40;

	glEnable(GL_TEXTURE_2D);

	if (initial)
	{
		glDisable(GL_TEXTURE_2D);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		
		glVertexPointer(3, GL_FLOAT, 0, stars);
		glColorPointer(4, GL_FLOAT, 0, starColors);
		glDrawArrays(GL_POINTS, 0, starsNum);
		
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
                glColor3f(1,1,1);
  	        glEnable(GL_TEXTURE_2D);

		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);

		glBindTexture(GL_TEXTURE_2D, moon->getId());
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                
        vec3 MoonPos(sin(moonTheta) * cos(moonPhi) * radius,
			    		cos(moonTheta) * radius,
			    		sin(moonTheta) * sin(moonPhi) * radius);

		Vertices[0] = (MoonPos + (-MoonSize*3) * (vx + vy) );		
		Vertices[1] = (MoonPos + (MoonSize*3)  * (vx - vy) );
		Vertices[2] = (MoonPos + (MoonSize*3)  * (vx + vy) ); 			
		Vertices[3] = (MoonPos + (MoonSize*3)  * (vy - vx) );

		glBegin(GL_QUADS);
			glTexCoord2f(1.0f , 0.0f); 
			glVertex3fv(Vertices[0].vec_array);
			glTexCoord2f(0.0f , 0.0f); 
			glVertex3fv(Vertices[1].vec_array);
			glTexCoord2f(0.0f , 1.0f); 
			glVertex3fv(Vertices[2].vec_array);
			glTexCoord2f(1.0f , 1.0f); 
			glVertex3fv(Vertices[3].vec_array);
		glEnd();	

		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
	}
	else
	{
   		vec3 SunPos(	sin(sunTheta) * cos(sunPhi) * radius,
			    		cos(sunTheta) * radius,
			    		sin(sunTheta) * sin(sunPhi) * radius);
					
		Vertices[0] = (SunPos +  (-SunSize * 3) * (vx + vy));		
		Vertices[1] = (SunPos +  (SunSize * 3)  * (vx - vy));
		Vertices[2] = (SunPos +  (SunSize * 3)  * (vx + vy)); 			
		Vertices[3] = (SunPos +  (SunSize * 3)  * (vy - vx));
			
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, sun->getId());
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
			
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f , 0.0f); 
			glVertex3fv(Vertices[0].vec_array);
			glTexCoord2f(0.0f , 0.0f); 
			glVertex3fv(Vertices[1].vec_array);
			glTexCoord2f(0.0f , 1.0f); 
			glVertex3fv(Vertices[2].vec_array);
			glTexCoord2f(1.0f , 1.0f); 
			glVertex3fv(Vertices[3].vec_array);
		glEnd();	

		glDisable(GL_BLEND);
   	}
	
	glDisable(GL_TEXTURE_2D);
}

