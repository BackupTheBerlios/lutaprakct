#ifndef LIGHT_H_
#define LIGHT_H_

class Light{

	public:
		Light(){canCastShadows = false;};
		virtual ~Light(){};
		
		//antes de chamar o initialize tem q setar os parametros
		virtual bool initialize(unsigned int id) = 0;
		virtual void shutdown() = 0;
		
		virtual void bind() = 0;
		virtual void unbind() = 0;
		
		void setPosition(float x, float y, float z, float w){
			position[0] = x; position[1] = y; position[2] = z; position[3] = w;
		}
	
		void setAmbient(float r, float g, float b, float a){
			ambient[0] = r; ambient[1] = g; ambient[2] = b; ambient[3] = a;
		}
		
		void setDiffuse(float r, float g, float b, float a){
			diffuse[0] = r; diffuse[1] = g; diffuse[2] = b; diffuse[3] = a;
		}
	
		unsigned int getId(){return id; };
		
		bool castShadows(){return canCastShadows; };
		void setShadowStatus(bool a){ canCastShadows = a;};
	
	protected:
	
		float position[4];
		float ambient[4];
		float diffuse[4];
		float specular[4];
		float itensity;
		float linear;
		float quadratic;
		unsigned int id;
		
		bool canCastShadows;
		bool attenuate;
		bool on;
		
		float exponent;
		float angle;
};


#endif /*LIGHT_H_*/
