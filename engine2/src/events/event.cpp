#include "event.h"

int translateEvent(const char* eventname){

	if (strcmp( eventname, "key_up"  ) == 0)
		return E_KEY_UP;
	else if  (strcmp( eventname, "key_down"  ) == 0)
		return E_KEY_DOWN;
	else if  (strcmp( eventname, "key_right"  ) == 0)
		return E_KEY_RIGHT;
	else if (strcmp( eventname, "key_left"  ) == 0)
		return E_KEY_LEFT;
	else if (strcmp( eventname, "key_w"  ) == 0)
		return E_KEY_W;
	else if (strcmp( eventname, "key_s"  ) == 0)
		return E_KEY_S;
	else if (strcmp( eventname, "key_esc"  ) == 0)
		return E_KEY_ESC;
	else if (strcmp( eventname, "key_f1"  ) == 0)
		return E_KEY_F1;
	else if (strcmp( eventname, "key_mouse_move"  ) == 0)
		return E_MOUSE_POSITION;
	
}
