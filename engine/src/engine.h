
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "util/interfaces/product.h"
#include "util/patterns/factories/videofactory.h"

#include "modules/video/videosystem.h"
#include "modules/input/eventhandler.h"
#include "modules/input/event.h"
#include "modules/camera/camera.h"
#include "modules/timer/timer.h"

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
 void update();
 void main();
 void handleEvent(const event &e);

private:
 bool done;
 videoSystem *video;
 camera *c;
 timer *t;
};


#endif

