#ifndef PROFILERLOGGER_H_
#define PROFILERLOGGER_H_

#include "profiler.h"

class ProfileLogHandler : public ProfilerOutputHandler  {
	
	public:
		void beginOutput(float tTime);
		void endOutput();
		void sample(float fMin, float fAvg, float fMax, float tAvg, int callCount, std::string name, int parentCount);
};

#endif /*PROFILERLOGGER_H_*/
