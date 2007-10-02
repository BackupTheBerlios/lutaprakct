#ifndef LIGHT_H_
#define LIGHT_H_

class Light{

	public:
		Light(){};
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
	
	protected:
	
		float position[4];
		float ambient[4];
		float diffuse[4];
		unsigned int id;
		
	
};


#endif /*LIGHT_H_*/
