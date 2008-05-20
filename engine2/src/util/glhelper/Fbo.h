#ifndef FBO_H_
#define FBO_H_

class Fbo{
	
	public:
		
		Fbo(){};
		~Fbo(){};
		
		bool addRenderBuffer(int sizex, int sizey);
		bool addDepthTexture(); //so pra fazer shadowmaps
		
		void initialize();
		
		void bind();
		void unbind();
		
		bool checkFramebufferStatus(bool silent);
		
	//private:
	
		unsigned int framebufferID;
		unsigned int renderbufferID;
		unsigned int shadowTextureID;
	
};

#endif /*FBO_H_*/
