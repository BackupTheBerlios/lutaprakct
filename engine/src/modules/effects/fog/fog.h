#ifndef FOG_H_
#define FOG_H_

enum{
	FOG_EXP = 1,
	FOG_EXP2,
	FOG_LINEAR
};

class Fog{
	
	public:
	
		Fog(float r, float g, float b, float a, float density, float start, float end, int mode);
		~Fog();
		
		void setColor(float r, float g, float b, float a);
		void setDensity( float density );
		void setStart( float start );
		void setEnd( float end );
		void setMode( int mode );
		
		void bind();
		void unbind();
	
};

#endif /*FOG_H_*/
