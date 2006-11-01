
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "threads.h"

unsigned int threads::Ticks(){
	
   timeval t;

   gettimeofday(&t, 0);
   return t.tv_sec * 1000 + t.tv_usec / 1000;
}

void threads::Delay(unsigned int dur){
   usleep(dur * 1000);
}

unsigned short threads::ShortEndian(unsigned short endi){
	
#ifndef WORDS_BIGENDIAN
   return(endi);
#endif
   // convert little endian to big endian
   return(((endi << 8) & 0xFF00) | ((endi >> 8) & 0x00FF));
}

unsigned int threads::LongEndian(unsigned int endi){
	
#ifndef WORDS_BIGENDIAN
   return(endi);
#endif
   return(((endi << 24) & 0xFF000000) | ((endi << 8) & 0x00FF0000) | ((endi >> 8) & 0x0000FF00) | ((endi >> 24) & 0x000000FF));
}


void threads::Thread::run(void* args) throw(errors::Exception){
	
   if(pthread_create(&handle, NULL, proc, args) != 0 )
      throw errors::Exception("Couldn't create console thread");
}
