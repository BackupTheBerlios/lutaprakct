#include "sound.h"
#include "soundsystem.h"
#include <iostream>
#include <cstring>

void sound::playogg(){	
	if (music){
		Mix_PlayMusic(music, 0);
	}else{
		music = Mix_LoadMUS(musicname.c_str());
		Mix_PlayMusic(music, 0);
	}
}

void sound::playwave() {
	if (wave) {
		Mix_PlayChannel(-1, wave, -1);
	} else {
		wave = Mix_LoadWAV(musicname.c_str());
		Mix_PlayChannel(-1, wave, -1);
	}
}