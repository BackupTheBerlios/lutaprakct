#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

#include "event.h"

/** interface que as classes que recebem eventos devem implementar. cada classe 
 * implementa o handleEvent da sua maneira, para tratar seus eventos.
 */

class EventHandler{

public:

    EventHandler();
    virtual ~EventHandler(){};
	virtual void handleEvent(const event &e) = 0; 
	
protected:

    void sendEvent(int eventType, int arg1 = 0, int arg2 = 0);
	
};

#endif //_EVENTHANDLER_H_
