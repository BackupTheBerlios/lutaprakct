
#include "eventdispatcher.h"
#include "event.h"

void EventDispatcher::addHandler(EventHandler *device){
	
	handlers.push_back(device);
	
}

void EventDispatcher::sendEvent(int eventType, int arg1, int arg2) {
  event e;
  e.type = eventType;
  e.arg1 = arg1;
  e.arg2 = arg2;
  
  std::list<EventHandler*>::iterator iter;
  
  for (iter = handlers.begin(); iter != handlers.end(); iter++)
    (*iter)->handleEvent(e);	
 
}
