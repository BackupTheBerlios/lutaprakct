
#include "logger.h"
#include <fstream>
#include <iostream>
#include <stdarg.h>

Logger::Logger(){
}

bool Logger::initialize(){
	
   if(!loadStrings())return false;

   return true;
}

void Logger::write(char* logfilename, const char* msg, ...){
	
	va_list args; va_start(args,msg);
	char szBuf[1024];
	vsprintf(szBuf,msg,args);

	std::ofstream out;
	out.open(logfilename, std::ios::out | std::ios::app);

	out << szBuf << std::endl;

#ifdef DEBUG
	out.flush();
#endif
   out.close();
   
}

void Logger::write(char* logfilename, unsigned long msgID, ...){
	
   va_list args; va_start(args, msgID);
   char szBuf[1024];
   vsprintf(szBuf,logStrings[msgID].c_str(),args);
   write(logfilename, szBuf);
}


bool Logger::loadStrings(){
	
	std::ifstream in("../data/logmessages.txt");
	if(!in.is_open())return false;

	unsigned long index=0;

	while(!in.eof()){	
		char szBuf[1024];
		in.getline(szBuf,1024);
		logStrings[index++]=szBuf;
	}

	return true;
}
