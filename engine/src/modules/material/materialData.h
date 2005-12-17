#ifndef _MATERIALDATA_H_
#define _MATERIALDATA_H_

struct materialData{
	
	float color[4];
	float secundaryColor[4];
	float shininess;
	float kEmissive[3], kAmbient[3], kDiffuse[3], kSpecular[3];
	
	
};

#endif //_MATERIALDATA_H_
