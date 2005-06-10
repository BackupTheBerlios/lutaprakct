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

void soundsystem::play(std::string filename) {
	std::list<sound*>::iterator iter;
	for (iter = sounds.begin(); iter != sounds.end(); iter++){
		if ( (*iter)->getMusicName() == filename){
			(*iter)->play();
			return;
		}
	}
	
	sound *s = new sound(filename);
	s->play();
	sounds.push_back(s);	
}

void soundsystem::shutdown() {
	Mix_CloseAudio();
}
