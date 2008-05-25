#ifndef MATERIAL_H_
#define MATERIAL_H_

class Material {
public:
	
	int type;
	float	emission[3];
	float	ambient[3];
	float	diffuse[3];
	float	specular[3];
	float	shininess;
	float	transparency;

	float	reflective[3];
	float	transparent[3];
	float	absorption[3];
	float	reflectivity;
	float	refractiveIndex;
	
 
	int		numTextures; 
	int		idx; 
	
	Material(domMaterial& mtl) {
		// Grab the <effect> from the <material> and initalize the parameters
	}
};

#endif /*MATERIAL_H_*/
