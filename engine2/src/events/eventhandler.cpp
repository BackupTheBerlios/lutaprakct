
#include "eventhandler.h"
#include "eventdispatcher.h"

/**contrutor ja adiciona o eventhandler na lista de handlers no dispatcher
 */

EventHandler::EventHandler(){
	EVENTDISPATCHER::getInstance().addHandler(this);
}

void EventHandler::sendEvent(int eventType, int arg1, int arg2){

	EVENTDISPATCHER::getInstance().sendEvent(eventType, arg1, arg2);
	
}
