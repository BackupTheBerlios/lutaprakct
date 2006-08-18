#ifndef FRUSTUM_H_
#define FRUSTUM_H_

class Frustum{
	
	public:
	
		void update();
		
		bool pointInFrustum(float x, float y, float z);
		bool sphereInFrustum(float x, float y, float z, float radius);
		bool cubeInFrustum( float x, float y, float z, float size );
	
	private:
	
		void normalizeFrustumPlane(int side);
		float planes[6][4];
	
	
};

#endif /*FRUSTUM_H_*/
