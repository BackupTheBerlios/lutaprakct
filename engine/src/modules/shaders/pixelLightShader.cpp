
#include "pixelLightShader.h"
#include "../camera/camera.h"
#include "../math/algebra.h"

#include <iostream>

void pixelLightShader::setInitialParameters(materialData *config){
	
    ModelViewProj = cgGetNamedParameter(vertexprogram, "modelViewProj");
	globalAmbient = cgGetNamedParameter(fragmentprogram, "globalAmbient");
	
	/* cria o array de luz de interfaces
	 * TODO: alguns passos devem ser feitos apenas 1 vez pelo light system*/
	 
    CGtype ltype = cgGetNamedUserType(fragmentprogram, "Light");
    CGtype ptype = cgGetNamedUserType(fragmentprogram, "PointLight");
    CGtype stype = cgGetNamedUserType(fragmentprogram, "SpotLight");
    
    // cria o array shared de luz (isso deveria ser feito 1 vez)
    CGparameter larray = cgCreateParameterArray(context, ltype, 2);

    // Cria cada luz (feito 1 vez)
    CGparameter plight = cgCreateParameter(context, ptype);
    CGparameter slight = cgCreateParameter(context, stype);
    
   // conecta cada luz ao parametro (feito 1 vez)
    cgConnectParameter(plight, cgGetArrayParameter(larray, 0));
    cgConnectParameter(slight, cgGetArrayParameter(larray, 1));

    // pega o parametro do shader
    CGparameter eparam = cgGetNamedParameter(fragmentprogram, "lights");

    // Conecta o shared parameter com o parametro do shader current
    cgConnectParameter(larray, eparam);

    CGparameter member;	
   // Initialize point light
    member = cgGetNamedStructParameter(plight, "Plight");
    cgSetParameter3f(member, -10, 10, 10);
    member = cgGetNamedStructParameter(plight, "Clight");
    cgSetParameter3f(member, .6, .6, .5);

    // Initialize spot light
    member = cgGetNamedStructParameter(slight, "Plight");
    cgSetParameter3f(member, 10, 10, 10);
    member = cgGetNamedStructParameter(slight, "Clight");
    cgSetParameter3f(member, .5, 1, .5);
    member = cgGetNamedStructParameter(slight, "target");
    cgSetParameter3f(member, 0., 0., 0.);
	
	eyePosition = cgGetNamedParameter(fragmentprogram, "eyePosition");
	ka = cgGetNamedParameter(fragmentprogram, "ka");
	kd = cgGetNamedParameter(fragmentprogram, "kd");
	ks = cgGetNamedParameter(fragmentprogram, "ks");
	shininess = cgGetNamedParameter(fragmentprogram, "shininess");
	
	/*material parameters */
	cgGLSetParameter3f(globalAmbient, 1.0, 1.0, 1.0);
	cgGLSetParameter3f(ka, config->kAmbient[0], config->kAmbient[1], config->kAmbient[2]);
	cgGLSetParameter3f(kd, config->kDiffuse[0], config->kDiffuse[1], config->kDiffuse[2]);
	cgGLSetParameter3f(ks, config->kSpecular[0], config->kSpecular[1], config->kSpecular[2]);
	cgGLSetParameter1f(shininess, config->shininess);
	
	compile();
	
}

void pixelLightShader::setLoopParameters(materialData *config){

	vec3 pos = Camera::getInstance().getPosition();
	cgGLSetParameter3f(eyePosition, pos.x, pos.y, pos.z );
	
    cgGLSetStateMatrixParameter(ModelViewProj, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	
}
