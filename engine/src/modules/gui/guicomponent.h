#ifndef GUICOMPONENT_H_
#define GUICOMPONENT_H_

class GuiComponent{
	
	public:
		
		GuiComponent(){};
		virtual ~GuiComponent(){};
		
		virtual void draw() = 0;
	
		void setColor(float r, float g, float b){
			color[0] = r; color[1] = g; color[2] = b;
		}
		
		void setColor(float r, float g, float b, float a){
			color[0] = r; color[1] = g; color[2] = b; color[3] = a;
		}
		
		void setPosition(int x, int y){
			position[0] = x; position[1] = y;
		}
		
		void setScale(float x, float y, float z){
			scale[0] = x; scale[1] = y; scale[2] = z;
		}
	
	protected:
	
		float color[4];
		int position[2];
		float scale[3];
		
};

#endif /*GUICOMPONENT_H_*/
