#ifndef MATERIAL_H_
#define MATERIAL_H_

class Material {
public:
	std::vector<float> diffuseColor;
	char* diffuseTexture;
	// ... and lots of other parameters
	
	Material(domMaterial& mtl) {
		// Grab the <effect> from the <material> and initalize the parameters
	}
};

#endif /*MATERIAL_H_*/
