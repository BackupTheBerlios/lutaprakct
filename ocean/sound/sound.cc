#include "sound.h"
#include "soundsystem.h"
#include <iostream>
void sound::play() {
	if (music){
		Mix_PlayMusic(music, 0);
	}else{
		music = Mix_LoadMUS(musicname.c_str());
		//if(music){ std::cout << "oi";}
		Mix_PlayMusic(music, 0);
	}
}
