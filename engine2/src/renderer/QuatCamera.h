#ifndef QUATCAMERA_H_
#define QUATCAMERA_H_

#include "../util/math/Pivot.h"
#include "../events/eventhandler.h"
#include "../util/patterns/Singleton.h"

 /** TODO rotatearound e positioncamera ?
  */
 
class QuatCamera : public EventHandler {
 	
public:

	QuatCamera(){};

 	void handleEvent(const event &e);
 	
 	void setupViewMatrix();

	Pivot<float> pivot;
};

typedef Singleton<QuatCamera> QUATCAMERA;


#endif /*QUATCAMERA_H_*/
