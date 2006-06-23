
#include "profilerLogger.h"
#include "../logger/logger.h"

#define IDS_PROFILE_HEADER1             1
#define IDS_PROFILE_HEADER2             2
#define IDS_PROFILE_SAMPLE              3

void ProfileLogHandler::beginOutput(float tTime){
	LOGGER::getInstance().write("profile.log", IDS_PROFILE_HEADER1, tTime, 60.0f/tTime);
	LOGGER::getInstance().write("profile.log", IDS_PROFILE_HEADER2);
}

void ProfileLogHandler::sample(float fMin, float fAvg, float fMax, float tAvg, int callCount, std::string name, int parentCount){
	//char szBuf[100];
	//for(int i=0;i<parentCount;i++){szBuf[i]=' ';}
	//szBuf[parentCount]=0;
	char namebuf[256], indentedName[256];
	char avg[16], min[16], max[16], num[16], time[16];

	sprintf(avg, "%3.1f", fAvg);
	sprintf(min, "%3.1f", fMin);
	sprintf(max, "%3.1f", fMax);
	sprintf(time,"%3.1f", tAvg);
	sprintf(num, "%3d",   callCount);

	strcpy( indentedName, name.c_str());
	for( int indent=0; indent<parentCount; ++indent )
	{
		sprintf(namebuf, " %s", indentedName);
		strcpy( indentedName, namebuf);
	}

	LOGGER::getInstance().write("profile.log", IDS_PROFILE_SAMPLE, min, avg, max, time, num, indentedName);
}

void ProfileLogHandler::endOutput(){
	LOGGER::getInstance().write("profile.log", "\n");
}
