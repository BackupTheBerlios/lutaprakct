#ifndef _EVENTDISPATCHER_H_
#define _EVENTDISPATCHER_H_

#include <list>
#include "eventhandler.h"
#include "../../util/singleton.h"

/** eventdispatcher eh um singleton que recebe os eventos do eventcore, e envia para todas as classes
 * que herdaram de eventhandler (ou seja todos da lista handlers)
 * normalmente essa classe eh inalterada pelo cliente, nao precisa mexer nela, pois sua funçao
 * é apenas interna do sistema de eventos.
 */

class eventDispatcher{
	
public:

  void addHandler(eventHandler *device);

  void sendEvent(int eventType, int arg1 = 0, int arg2 = 0);

private:
  std::list<eventHandler*> handlers;
};

typedef singleton<eventDispatcher> EventDispatcher;

#endif //_EVENTDISPATCHER_H_
