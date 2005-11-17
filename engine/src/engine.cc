
#include "engine.h"
#include "modules/input/core/sdlinputcore.h"
#include "util/meshio/obj/objload.h"
#include "util/meshio/md2/md2IO.h"

#include "modules/textures/texture.h"
#include "modules/textures/texturemanager.h"

#include "modules/math/algebra.h"

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

unsigned int nverts = 0;
unsigned int nindices = 0;
unsigned int *indices = NULL;
float *vertexdata = NULL;
float *normaldata = NULL;
float *tangendata = NULL;
float *binormdata = NULL;
float *texcoords = NULL;

GLfloat LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 	
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };	
GLfloat LightPosition[]= { 0.0f, -200.0f, -200.0f, 1.0f };

md2IO *model;
engine::engine(){ 
	done = false;
}

engine::~engine(){
}

texture *tex;
	
bool engine::initialize(){

	std::cout << "Inicializando Engine..." << std::endl;

	video = (videoSystem*)VideoFactory::getInstance().create("sdlvideo");
	if (!video->initialize( videoSystem::RES_800x600 | videoSystem::BPP_8 | videoSystem::OPENGL ))
		return false;
	video->setWindowTitle("Engine");
    video->showCursor(false);

	//precisa informar o tamanho da janela pro inpurCore calcular o quanto o mouse deslocou-se
	InputCore::getInstance().informWindowSize(video->getWidth(), video->getHeight());
	InputCore::getInstance().setMouseVelocity(10.0);
	
    c = new camera();
    t = new timer();
    
    std::cout << "Engine inicializada com sucesso!" << std::endl;  
    
    LoadObjModel("Raygun_01.OBJ",nverts,nindices,indices,vertexdata,normaldata,tangendata,binormdata,texcoords);
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
    glEnable(GL_LIGHT1);
//    model = new 	md2IO();
 //   model->ReadFile("Tris.MD2");
 //  tex = TextureManager::getInstance().load("ogro2.tga", texture::TEXTURE_2D, texture::CLAMP | texture::RGB | texture::LINEAR_MIPMAP_LINEAR);
	tex = TextureManager::getInstance().load("rock.tga", texture::TEXTURE_2D, texture::CLAMP | texture::RGB | texture::LINEAR_MIPMAP_LINEAR);   
	return true;
	
}

void engine::shutdown(){
	if (video)
		delete video;
}

void engine::draw(){
	video->lock();


	//glLoadIdentity();
	glEnable(GL_LIGHTING);
	glPushMatrix();
	glRotatef(40.7,1.0f,1.0f,1.0f);	
    glVertexPointer(3, GL_FLOAT, 0, vertexdata);
    glNormalPointer(GL_FLOAT, 0, normaldata);
    glTexCoordPointer( 2, GL_FLOAT, 0, texcoords );
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    tex->enable();
    tex->bind();
    glDrawElements(GL_TRIANGLES, nindices, GL_UNSIGNED_INT, indices);
//    model->AnimateModel(0, 100, 0.01);
    glPopMatrix();
	glTranslatef(1.5f,0.0f,-70.0f);				// Move Right And Into The Screen
/*tex->enable();
tex->bind();
	glRotatef(70.7,1.0f,1.0f,1.0f);			// Rotate The Cube On X, Y & Z
	glBegin(GL_QUADS);					// Start Drawing The Cube

		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	
					

		/*glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Green
		glVertex3f( 10.0f, 10.0f,-10.0f);			// Top Right Of The Quad (Top)
		glVertex3f(-10.0f, 10.0f,-10.0f);			// Top Left Of The Quad (Top)
		glVertex3f(-10.0f, 10.0f, 10.0f);			// Bottom Left Of The Quad (Top)
		glVertex3f( 10.0f, 10.0f, 10.0f);			// Bottom Right Of The Quad (Top)

		

		glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
		glVertex3f( 10.0f,-10.0f, 10.0f);			// Top Right Of The Quad (Bottom)
		glVertex3f(-10.0f,-10.0f, 10.0f);			// Top Left Of The Quad (Bottom)
		glVertex3f(-10.0f,-10.0f,-10.0f);			// Bottom Left Of The Quad (Bottom)
		glVertex3f( 10.0f,-10.0f,-10.0f);			// Bottom Right Of The Quad (Bottom)


		glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
		glVertex3f( 10.0f, 10.0f, 10.0f);			// Top Right Of The Quad (Front)
		glVertex3f(-10.0f, 10.0f, 10.0f);			// Top Left Of The Quad (Front)
		glVertex3f(-10.0f,-10.0f, 10.0f);			// Bottom Left Of The Quad (Front)
		glVertex3f( 10.0f,-10.0f, 10.0f);			// Bottom Right Of The Quad (Front)

		

		glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
		glVertex3f( 10.0f,-10.0f,-10.0f);			// Bottom Left Of The Quad (Back)
		glVertex3f(-10.0f,-10.0f,-10.0f);			// Bottom Right Of The Quad (Back)
		glVertex3f(-10.0f, 10.0f,-10.0f);			// Top Right Of The Quad (Back)
		glVertex3f( 10.0f, 10.0f,-10.0f);			// Top Left Of The Quad (Back)

			

		glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
		glVertex3f(-10.0f, 10.0f, 10.0f);			// Top Right Of The Quad (Left)
		glVertex3f(-10.0f, 10.0f,-10.0f);			// Top Left Of The Quad (Left)
		glVertex3f(-10.0f,-10.0f,-10.0f);			// Bottom Left Of The Quad (Left)
		glVertex3f(-10.0f,-10.0f, 10.0f);			// Bottom Right Of The Quad (Left)


		glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
		glVertex3f( 10.0f, 10.0f,-10.0f);			// Top Right Of The Quad (Right)
		glVertex3f( 10.0f, 10.0f, 10.0f);			// Top Left Of The Quad (Right)
		glVertex3f( 10.0f,-10.0f, 10.0f);			// Bottom Left Of The Quad (Right)
		glVertex3f( 10.0f,-10.0f,-10.0f);			// Bottom Right Of The Quad (Right)
	glEnd();						// Done Drawing The Quad
*/
	video->unlock();
}

void engine::update(){
	//TODO passar o tempo
	t->update();
	c->update(t->getSPF());
}


void engine::main(){

	while(!done){
		draw();
		InputCore::getInstance().doInput();
		update();
	}
	
}

void engine::handleEvent(const event &e){

	switch (e.type) {
      case E_APPCLOSE:
        done = true;
        break;
    }
	
	
}
	

int main()
{
	engine eng;
	eng.initialize();
	eng.main();
	eng.shutdown();
	return 0;
}
