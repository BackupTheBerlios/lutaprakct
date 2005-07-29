#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

#include "event.h"


class eventHandler{

public:

	virtual void handleEvent(const event &e) = 0; 
	
};


#endif //_EVENTHANDLER_H_

