#ifndef _EVENT_H_
#define _EVENT_H_

enum eventType
{
  E_APPCLOSE
};

struct event {
  int type;
  int arg1, arg2;
};

#endif //_EVENT_H_
