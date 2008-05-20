#ifndef _EVENT_H_
#define _EVENT_H_

#include <cstring>

/** apenas a definicao da enum dos eventos, sempre que for adicionar um event novo
 * modifique esta enum.
 * a struct event eh simples e talvez nunca precise de alteracao.
 */

enum eventType
{
  E_APPCLOSE,
  
  E_KEY_UP,
  E_KEY_DOWN,
  E_KEY_LEFT,
  E_KEY_RIGHT,
  
  E_KEY_W,
  E_KEY_S,
  
  E_KEY_ESC,
  
  E_KEY_F1,
  
  E_MOUSE_ROTATE_X,
  E_MOUSE_ROTATE_Y,

  E_MOUSE_POSITION
  
};

struct event {
  int type;
  int arg1, arg2;
};

int translateEvent(const char* eventname);

#endif //_EVENT_H_
