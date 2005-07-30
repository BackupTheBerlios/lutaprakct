
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "modules/video/videosystem.h"
#include "modules/sound/soundsystem.h"


#include "modules/input/eventhandler.h"
#include "modules/input/event.h"

#include "modules/game/gamemanager.h"

/** classe basica de controle da engine. As instancias
    dos sub sistemas ficam nessa classe.
*/

class engine : public eventHandler{
 
public:
	engine();
	~engine();

	bool initialize();
	void shutdown();
	void draw();
	void drawbackground();
	void update();
	void main();
	void clear();
	void handleEvent(const event &e);

private:
	bool done;
	videosystem *video;
	soundsystem *som;
	gameManager manager;

	int firstx, firsty, secondx, secondy;
	bool pressioned;

};


#endif
