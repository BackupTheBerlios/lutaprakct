#ifndef PARTICLE_H_
#define PARTICLE_H_

/* classe basica da particle, outras parciles podem herdar dessa
 * e acrescentar shaders, fisica ou apenas mais atributos
 * as subclasses devem ter o metodo render() pois dependendo
 * do tipo de particula os comandos para desenha-la
 * sao diferentes (ou elas teriam um renderer)
 * */

class Particle{
	
	public:

		Particle(){};
		virtual ~Particle(){};
		
		float position[3];
		float force[3];
		float velocity[3];
		float color[4];
		float size;
		float life;
		float fade;

};

#endif /*PARTICLE_H_*/
