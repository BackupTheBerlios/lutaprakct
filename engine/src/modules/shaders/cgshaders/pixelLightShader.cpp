
#include "pixelLightShader.h"
#include "../../renderer/camera/camera.h"
#include "../../../util/math/algebra.h"
#include "../../material/materialData.h"

#include <iostream>

void PixelLightShader::setInitialParameters(void* config){
	
	MaterialData* mat = (MaterialData*)config;
	
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
	cgGLSetParameter3f(ka, mat->kAmbient[0], mat->kAmbient[1], mat->kAmbient[2]);
	cgGLSetParameter3f(kd, mat->kDiffuse[0], mat->kDiffuse[1], mat->kDiffuse[2]);
	cgGLSetParameter3f(ks, mat->kSpecular[0], mat->kSpecular[1], mat->kSpecular[2]);
	cgGLSetParameter1f(shininess, mat->shininess);
	
	compile();
	
}

void PixelLightShader::setLoopParameters(void* config){

	vec3 pos; //= CAMERA::getInstance().getPosition();
	cgGLSetParameter3f(eyePosition, pos.x, pos.y, pos.z );
	
    cgGLSetStateMatrixParameter(ModelViewProj, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	
}
