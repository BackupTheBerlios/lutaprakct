#ifndef ATMOSPHERICSHADER_H_
#define ATMOSPHERICSHADER_H_

#include "../../../util/glhelper/glslShader.h"
#include "../../../util/math/algebra.h"
#include <cmath>

const char* atmosphericVertexSource =
"vec3 betaRay = vec3(0.000061, 0.000103, 0.000215); \n"
"vec3 betaMie = vec3(0.000045, 0.000059, 0.000084); \n"
"vec3 greenstein = vec3(-2.4, 1.44, 0.04 ); \n"
"vec3 camera = vec3(103.13, 30.3865, 51.9579); \n"
"vec3 energy = vec3(9321.9, 6137.16, 3341.81); \n"
"vec3 L = vec3 (-0.544894, -0.787612, 0.287677);	\n"
"varying vec3 L_in;	\n"
"varying vec3 F_ex;	\n"
"void main(){															\n"
"	vec4 ecPosition = gl_ModelViewMatrix * gl_Vertex; \n"
"	vec3 viewDir = normalize(camera - ecPosition.xyz); \n"
"	float cos = dot(viewDir, L); \n"
"	float s = distance(camera, ecPosition.xyz); \n"
"	F_ex = exp ( (betaRay + betaMie)*(-s) ); \n"
"	vec3 Br = 0.0597 * betaRay * (cos*cos + 1.0); \n"
"	vec3 Bm = 0.0796 * betaMie * greenstein.z/( greenstein.y + pow((greenstein.x*cos), 1.5) ); \n"
"//	L_in = ((Br + Bm)/(betaRay+betaMie))*(1.0 - F_ex); \n"
"	L_in = 1.0 - F_ex; \n"
"	gl_Position = ftransform();								\n"
"}																		\n\0";

const char* atmosphericFragmentSource =
"varying vec3  L_in;													\n"
"varying vec3 F_ex;														\n"
"void main(){															\n"
"	vec3 color = F_ex + L_in;													\n"
"    gl_FragColor = vec4(L_in, 1.0);									\n"
"}																		\n\0";


class AtmosphericShader : public GlslShader{
	
	public:
	
		AtmosphericShader(){};
		AtmosphericShader(const char* vertexSource, const char* fragmentSource){ initialize(vertexSource, fragmentSource);};
		~AtmosphericShader(){kill();};
		
		void setInitialParameters(){
			vec3 lambda(1.0/ 65e-9, 1.0/570-9, 1.0/475e-9);
			vec3 lambda2;
			vec3 lambda4;
			for (int i = 0; i < 3; i++){
				lambda2[i] = lambda[i] * lambda[i];
				lambda4[i] = lambda2[i] * lambda2[i];
			}
			float n = 1.003;
			float N = 2.545e25;
			float pn = 0.035;
			float T = 2.0;
			float c = (6.544 * T - 6.51) * 1e-17;
			
			float tempRay = pi * pi * (n*n - 1.0) * (n*n - 1.0) * (6.0 + 3.0*pn) / (6.0 - 7.0*pn) / N;
			betaRay =  (8.0 * tempRay * pi / 3.0) * lambda4;
			
			float tempMie = 0.434 * c * pi * (2*pi)*(2*pi)*0.5;
			betaMie = vec3(lambda2.x*0.685, lambda2.y*0.679, lambda2.z*0.67);
			betaMie = tempMie * betaMie;
			
			greenstein = 0.8 * 1.5;
			energy = 10.0 * 1.0;
			
			betaRay *= 0.8*1.1;
			betaMie *= 0.2*0.8;
		};
		
		void setLoopParameters(){
				/*GLint loc = glGetUniformLocationARB(program, "L");
				if (loc == -1){
					std::cout << "uniform sundir nao encontrada" << std::endl;
	    			//return;	
				}
				vec3 sundir = vec3(sin(4.0/10.0), cos(4.0/10.0), 0.1 + fabs(sin(4.0/30.0)));
				sundir.normalize();
				glUniform3fARB( loc, sundir.x, sundir.y, sundir.z );
				*/
				/*GLint loc = glGetUniformLocationARB(program, "betaRay");
				if (loc == -1){
					std::cout << "uniform betaRay nao encontrada" << std::endl;
	    			//return;	
				}
				glUniform3fARB( loc, betaRay.x, betaRay.y, betaRay.z );
				
				loc = glGetUniformLocationARB(program, "betaMie");
				if (loc == -1){
					std::cout << "uniform betMie nao encontrada" << std::endl;
	    			//return;	
				}
				glUniform3fARB( loc, betaMie.x, betaMie.y, betaMie.z );
				*/
				/*loc = glGetUniformLocationARB(program, "a");
				if (loc == -1){
					std::cout << "uniform energyOverRayMie nao encontrada" << std::endl;
	    			//return;	
				}
				vec3 energy2 = vec3( energy/(betaRay.x + betaMie.x), energy / (betaRay.y + betaMie.y), energy / (betaRay.z + betaMie.z) );
				glUniform3fARB( loc, energy2.x, energy2.y, energy2.z );				
				*/
				/*loc = glGetUniformLocationARB(program, "greenstein");
				if (loc == -1){
					std::cout << "uniform G nao encontrada" << std::endl;
	    			//return;	
				}
				vec3 g = vec3( -greenstein*2.0, greenstein*greenstein+1.0, (1.0 - greenstein)*(1.0-greenstein) );
				glUniform3fARB( loc, g.x, g.y, g.z );*/
				
				/*loc = glGetUniformLocationARB(program, "camera");
				if (loc == -1){
					std::cout << "uniform camera nao encontrada" << std::endl;
	    			//return;	
				}
				vec3 g = vec3( 103.13f, 30.3865f, 51.9579f );
				glUniform3fARB( loc, g.x, g.y, g.z );				
				*/
		};
		
	private:
		vec3 betaRay;
		vec3 betaMie;
		float greenstein;
		float energy;
};


#endif /*ATMOSPHERICSHADER_H_*/
