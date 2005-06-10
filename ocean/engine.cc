#include "sound/soundsystem.h"
#include "sound/sound.h"
#include "engine.h"
#include "drawfunctions.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

engine::engine(){ 
	done = false;
}

engine::~engine(){
}

void engine::drawbackground(){
	video->lock();
		drawgrid(SDL_GetVideoSurface(), video->getWidth(), video->getHeight(), 10, 255, 255,255);
 	video->unlock();
}

void engine::clear(){
	video->lock();
		SDL_FillRect(SDL_GetVideoSurface(),NULL,0x000000);
	video->unlock();
}
	
bool engine::initialize(){

	video = new videosystem();
	if (!video->initialize(videosystem::HWSURFACE | videosystem::DOUBLEBUF | videosystem::RES_800x600 | videosystem::BPP_8))
		return false;
	video->setWindowTitle("Ocean");
	
	som = new soundsystem();
	som->initialize(22050, AUDIO_S16, 2, 4096);
	som->play("Hydrate-Kenny_Beltrey.ogg");
	return true;
	
}

void engine::shutdown(){
	if (video)
		delete video;
}

void engine::draw(){
	video->lock();

	video->unlock();
}

void engine::update(){
}

void engine::main(){

	while(!done){
		draw();
		doInput();
	}
	
}

void engine::doInput(){
	
	fflush(stdout);
	fflush(stdin);
	SDL_Event event;
	while( SDL_PollEvent( &event ) ){
		
		switch( event.type ){
			case SDL_QUIT:
				done = true;//exit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch(event.button.button){
			    	case SDL_BUTTON_LEFT:
    			 		break;
    				default:
     					break;
   				}
   				break;
  			case SDL_KEYDOWN:
   				switch( event.key.keysym.sym ){

     				case SDLK_ESCAPE:
					//       exit = true;
       					break;
     				default:
       					break;
    			}
   
  			default:
   				break;
  			}
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
