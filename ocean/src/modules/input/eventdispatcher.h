#ifndef _EVENTDISPATCHER_H_
#define _EVENTDISPATCHER_H_

#include <list>
#include "eventhandler.h"
#include "../../util/singleton.h"

class eventDispatcher{
	
public:

  void addHandler(eventHandler *device);

  void sendEvent(int eventType, int arg1 = 0, int arg2 = 0);

private:
  std::list<eventHandler*> handlers;
};

typedef singleton<eventDispatcher> inputdispatcher;

#endif //_EVENTDISPATCHER_H_
