#ifndef _EVENT_H_
#define _EVENT_H_

/** apenas a definicao da enum dos eventos, sempre que for adicionar um event novo
 * modifique esta enum.
 * a struct event eh simples e talvez nunca precise de alteracao.
 */

enum eventType
{
  E_APPCLOSE
};

struct event {
  int type;
  int arg1, arg2;
};

#endif //_EVENT_H_
