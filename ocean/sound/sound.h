#ifndef _SOUND_H_
#define _SOUND_H_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <string>

class sound {
public:
	void play();
	void free_memory();
	void halt();
	sound(std::string filename) { musicname = filename; music = 0; };
	~sound(){};
		
	std::string getMusicName(){ return musicname; };
private:
	Mix_Music *music;
	std::string musicname;
};
#endif
