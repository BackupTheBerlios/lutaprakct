#ifndef LIGHT_H_
#define LIGHT_H_

//classe de luz BEM simples, so algumas coisas basicas
//TODO adicionar outros tipos de light e metodos get

class Light{

	public:
		Light();
		~Light();
		
		//antes de chamar o initialize tem q setar os parametros
		bool initialize(unsigned int id);
		void shutdown();
		
		void bind();
		void unbind();
		
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
	
	private:
	
		float position[4];
		float ambient[4];
		float diffuse[4];
		unsigned int id;
		
	
};

#endif /*LIGHT_H_*/
