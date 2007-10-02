
#include <iostream>
#include "ShLight.h"

const char* vertexSource =
"varying vec3 DiffuseColor;	\n" 
"const float C1 = 0.429043; \n"
"const float C2 = 0.511664; \n"
"const float C3 = 0.743125; \n"
"const float C4 = 0.886227; \n"
"const float C5 = 0.247708; \n"
"// Constants for Grace Cathedral lighting \n"
"const vec3 L00  = vec3( 0.78908,  0.43710,  0.54161); \n"
"const vec3 L1m1 = vec3( 0.39499,  0.34989,  0.60488); \n"
"const vec3 L10  = vec3(-0.33974, -0.18236, -0.26940); \n"
"const vec3 L11  = vec3(-0.29213, -0.05562,  0.00944); \n" 
"const vec3 L2m2 = vec3(-0.11141, -0.05090, -0.12231); \n"
"const vec3 L2m1 = vec3(-0.26240, -0.22401, -0.47479); \n" 
"const vec3 L20  = vec3(-0.15570, -0.09471, -0.14733); \n"
"const vec3 L21  = vec3( 0.56014,  0.21444,  0.13915); \n"
"const vec3 L22  = vec3( 0.21205, -0.05432, -0.30374); \n"
"void main()																	\n"
"{																				\n"
"    vec3 tnorm    = normalize(gl_NormalMatrix * gl_Normal);					\n"   
"    DiffuseColor =  C1 * L22 * (tnorm.x * tnorm.x - tnorm.y * tnorm.y) +		\n"
"                    C3 * L20 * tnorm.z * tnorm.z +								\n"
"                    C4 * L00 -													\n"
"                    C5 * L20 +													\n"
"                    2.0 * C1 * L2m2 * tnorm.x * tnorm.y +						\n"
"                    2.0 * C1 * L21  * tnorm.x * tnorm.z +						\n"
"                    2.0 * C1 * L2m1 * tnorm.y * tnorm.z +						\n"
"                    2.0 * C2 * L11  * tnorm.x +								\n"
"                    2.0 * C2 * L1m1 * tnorm.y +   								\n"
"                    2.0 * C2 * L10  * tnorm.z;   								\n"
"    DiffuseColor *= 1.0;    											\n"
"    gl_Position = ftransform();												\n"
"}																				\n\0";

const char* fragmentSource = 
"varying vec3 DiffuseColor;						\n"
"void main()									\n"
"{												\n"
"    gl_FragColor = vec4(DiffuseColor, 1.0);	\n"
"}												\n\0";


ShLight::ShLight(){
}

ShLight::~ShLight(){
}

bool ShLight::initialize(unsigned int id){
	
	if (!shader.initialize(vertexSource, fragmentSource))
		return false;
	std::cout << shader.getCompilerLog() << std::endl;
	
	return true;
}

void ShLight::shutdown(){

	shader.kill();	
}

void ShLight::bind(){
	shader.bind();
}

void ShLight::unbind(){
	shader.unbind();
}
