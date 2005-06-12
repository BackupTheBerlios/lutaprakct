#include "soundsystem.h"
#include <iostream>
#include <algorithm>

bool soundsystem::initialize(int frequency, Uint16 format, int channels, int chunksize) {
	audio_rate = frequency;
	audio_format = format;
	audio_channels = channels;
	audio_buffer = chunksize;
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffer)){
	std::cout << "Nao foi possivel inicializar o audio" << std::endl;
	}
}

int soundsystem::check(const char *musname){
	
	char *Ptr = strchr(musname, '.');
	Ptr++;
	if ( strcmp(Ptr, "wmv") == 0 ){
		return 2;
	} else if ( strcmp(Ptr, "ogg") == 0) {
		return 1;
	}
}

void soundsystem::play(std::string filename) {
	std::list<sound*>::iterator iter;
	for (iter = sounds.begin(); iter != sounds.end(); iter++){
		if ( (*iter)->getMusicName() == filename){
			if (check(filename.c_str()) == 1) {
				(*iter)->playogg();
				 return;
			} else if (check(filename.c_str()) == 2) {
				(*iter)->playwave();
				 return;	 
		}
	}
	
	sound *s = new sound(filename);
	s->playogg();
	sounds.push_back(s);	
}
}
/*
void soundsystem::shutdown() {
	Mix_CloseAudio();
} */
