

#include "entity.h"
#include "../sprites/spriteManager.h"
#include "../sprites/spritebase.h"
#include "../video/videosystem.h"
#include <iostream>

entity::~entity(){
}


entity::entity(std::string filename){
	this->filename = filename;
	spriteBase *newbase = SpriteManager::getInstance().load(filename);
	img.initialize(newbase, VideoSystem::getInstance().getScreen());
	//TODO essas funçoes sao so pra teste:
	img.set(450, 50);
	img.setSpeed(1);	
	
}

void entity::setx(long int x){
	this->x = x;
}

void entity::sety(long int y){
	this->y = y;
}

void entity::draw(){
	img.clearBG();
	img.updateBG();
	img.draw();
}