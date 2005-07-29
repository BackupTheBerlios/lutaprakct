
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "modules/video/videosystem.h"
#include "modules/sound/soundsystem.h"


/** classe basica de controle da engine. As instancias
    dos sub sistemas ficam nessa classe.
*/

class engine{
 
public:
 engine();
 ~engine();

 bool initialize();
 void shutdown();
 void draw();
 void drawbackground();
 void update();
 void main();
 void doInput();
 void clear();

private:
 bool done;
 videosystem *video;
 soundsystem *som;

 int firstx, firsty, secondx, secondy;
 bool pressioned;

};


#endif
