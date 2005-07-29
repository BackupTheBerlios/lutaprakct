
#ifndef _SOUNDSYSTEM_H_
#define _SOUNDSYSTEM_H_

#include <SDL/SDL_mixer.h>
#include <string>
#include <list>
#include "sound.h"
#include <algorithm>

class soundsystem{
public:
	int check(const char *musname);
	bool initialize(int frequency, Uint16 format, int channels, int chunksize);
	void play(std::string filename);
	void shutdown();		
	soundsystem () {};
	~soundsystem () {};
		
private:
	int audio_rate;
	Uint16 audio_format;
	int audio_channels;
	int audio_buffer;
	std::list<sound*> sounds;
	
};

#endif
