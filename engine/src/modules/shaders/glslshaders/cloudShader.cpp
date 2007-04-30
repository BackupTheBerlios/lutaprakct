
#include "cloudShader.h"
#include <iostream>

//Scale defaultl 0.001 0.0009
const char* cloudVertexSource = 
"varying vec3  teste; 												\n"
"float Scale = 0.0009;													\n"
"void main(){															\n"
"   teste      = vec3(gl_Vertex) * Scale;							\n"
"   gl_Position     = ftransform();										\n"
"}																		\n\0";

const char* cloudFragmentSource =
"//varying vec3  teste;																			\n"
"uniform sampler3D Noise;																			\n"
"vec3 SkyColor = vec3(0.0, 0.0, 0.8);																\n"
"uniform vec3 Offset; 																				\n"
"vec3 CloudColor = vec3(1.0, 1.0, 1.0);																\n"
"void main(){																						\n"
"    vec4  noisevec  = texture3D(Noise, gl_TexCoord[0].xyz + Offset);										\n"
"    float intensity = (noisevec[0] + noisevec[1] + noisevec[2] + noisevec[3] + 0.03125) * 1.5;		\n"
"    vec3 color   = mix(SkyColor, CloudColor, intensity);										\n"
"    gl_FragColor = vec4(color, 1.0);																\n"
"}																									\n\0";


void CloudShader::setInitialParameters(){

	animation[0] = 0.0;
	animation[1] = 0.0;
	animation[2] = 0.0;

	//GLint loc = glGetUniformLocationARB(program, "Noise");
	GLint loc = glGetUniformLocationARB(program, "s_texture_0");
	if (loc == -1){
		std::cout << "uniform 1 nao encontrada" << std::endl;
	    	return;	
	}
	glUniform1iARB( loc, 0);
	
	glGetUniformLocationARB(program, "s_texture_1");	
	glUniform1iARB( loc, 1);	
	
	time = glGetUniformLocationARB(program, "time");
	if (time == -1)
	    	return;
		
	return;
	
}

void CloudShader::setLoopParameters(){


	
	animation[2] += 0.0003;
	animation[1] += 0.0001;
	
	glUniform1fARB( time, animation[1]);	
	return;
	
}
