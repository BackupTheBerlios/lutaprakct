
#include "eventhandler.h"
#include "eventdispatcher.h"

/**contrutor ja adiciona o eventhandler na lista de handlers no dispatcher
 */

eventHandler::eventHandler(){
	EventDispatcher::getInstance().addHandler(this);
}

void eventHandler::sendEvent(int eventType, int arg1, int arg2){

	EventDispatcher::getInstance().sendEvent(eventType, arg1, arg2);
	
}
