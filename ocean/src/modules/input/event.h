#ifndef _EVENT_H_
#define _EVENT_H_

/** apenas a definišao da enum dos eventos, sempre que for adicionar um event novo
 * modifique esta enum.
 * a struct event eh simples e talvez nunca precise de alterašao.
 */

enum eventType
{
  E_APPCLOSE,
  E_LEFT,
  E_RIGHT,
  E_UP,
  E_DOWN
};

struct event {
  int type;
  int arg1, arg2;
};

#endif //_EVENT_H_
