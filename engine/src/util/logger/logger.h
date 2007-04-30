#ifndef LOGGER_H_
#define LOGGER_H_

#include "../patterns/singleton.h"
#include <string>

#define MAX_LOG_STRINGS 256

class Logger  {
	
	private:
	
		std::string logStrings[MAX_LOG_STRINGS];
		bool loadStrings();
   
	public:
   
   		Logger();
		bool initialize();
   
		void write(char* logfilename, const char* msg, ...);
		void write(char* logfilename, unsigned long msgID, ...);
};

typedef Singleton<Logger> LOGGER;

#endif /*LOGGER_H_*/
