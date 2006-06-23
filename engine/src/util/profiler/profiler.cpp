
#include "profiler.h"
#include <cassert>

int ProfileSample::lastOpenedSample=-1;
int ProfileSample::openSampleCount=0;
ProfileSample::profileSample ProfileSample::samples[MAX_PROFILER_SAMPLES];
ProfilerOutputHandler *ProfileSample::outputHandler=0;
float ProfileSample::rootBegin=0.0f;
float ProfileSample::rootEnd=0.0f;
bool ProfileSample::isRunning=true;

ProfileSample::ProfileSample(std::string sampleName){
	
	if(!isRunning)return;
	//find the sample
	int i=0;
	int storeIndex=-1;
	for(i=0;i<MAX_PROFILER_SAMPLES;++i){
		
		if(!samples[i].isValid){
			
			if(storeIndex<0)
				storeIndex=i;
			}else{
				if(samples[i].name==sampleName){
					//this is the sample we want
					//check that it's not already open
					assert(!samples[i].isOpen && "Tried to profile a sample which was already being profiled");
					//first, store it's index
					sampleIndex=i;
					//the parent sample is the last opened sample
					parentIndex=lastOpenedSample;
					lastOpenedSample=i;
					samples[i].parentCount=openSampleCount;
					++openSampleCount;
					samples[i].isOpen=true;
					++samples[i].callCount;
					samples[i].startTime=getTime();
					//if this has no parent, it must be the 'main loop' sample, so do the global timer
					if(parentIndex<0)
						rootBegin=samples[i].startTime;
					return;
				}
			}
		}
		//we've not found it, so it must be a new sample
		//use the storeIndex value to store the new sample
		assert(storeIndex>=0 && "Profiler has run out of sample slots!");
		samples[storeIndex].isValid=true;
		samples[storeIndex].name=sampleName;
		sampleIndex=storeIndex;
		parentIndex=lastOpenedSample;
		lastOpenedSample=storeIndex;
		samples[i].parentCount=openSampleCount;
		openSampleCount++;
		samples[storeIndex].isOpen=true;
		samples[storeIndex].callCount=1;

		samples[storeIndex].totalTime=0.0f;
		samples[storeIndex].childTime=0.0f;
		samples[storeIndex].startTime=getTime();
		if(parentIndex<0)
			rootBegin=samples[storeIndex].startTime;
}

ProfileSample::~ProfileSample(){
	
	if(!isRunning)
		return;
		
	float fEndTime=getTime();
	//phew... ok, we're done timing
	samples[sampleIndex].isOpen=false;
	//calculate the time taken this profile, for ease of use later on
	float fTimeTaken = fEndTime - samples[sampleIndex].startTime;

	if(parentIndex>=0){
		samples[parentIndex].childTime+=fTimeTaken;
	}else{
		//no parent, so this is the end of the main loop sample
		rootEnd=fEndTime;
	}
	samples[sampleIndex].totalTime+=fTimeTaken;
	lastOpenedSample=parentIndex;
	--openSampleCount;
}

void ProfileSample::output(){
	
	if(!isRunning)return;

	assert(outputHandler && "Profiler has no output handler set");
	
	outputHandler->beginOutput(rootEnd-rootBegin);

	for(int i=0;i<MAX_PROFILER_SAMPLES; ++i){
		if(samples[i].isValid){
			float sampleTime, percentage;
			//calculate the time spend on the sample itself (excluding children)
			sampleTime = samples[i].totalTime-samples[i].childTime;
			percentage = ( sampleTime / ( rootEnd - rootBegin ) ) * 100.0f;

			//add it to the sample's values
			float totalPc;
			totalPc=samples[i].averagePc*samples[i].dataCount;
			totalPc+=percentage; samples[i].dataCount++;
			samples[i].averagePc=totalPc/samples[i].dataCount;
			if((samples[i].minPc==-1)||(percentage<samples[i].minPc))samples[i].minPc=percentage;
			if((samples[i].maxPc==-1)||(percentage>samples[i].maxPc))samples[i].maxPc=percentage;

			//output these values
			outputHandler->sample(samples[i].minPc,
					      samples[i].averagePc,
					      samples[i].maxPc,
					      sampleTime,
					      samples[i].callCount,
					      samples[i].name,
					      samples[i].parentCount);

			//reset the sample for next time
			samples[i].callCount=0;
			samples[i].totalTime=0;
			samples[i].childTime=0;
		}
	}

	outputHandler->endOutput();
}

void ProfileSample::resetSample(std::string strName){
	
	for(int i=0;i<MAX_PROFILER_SAMPLES; ++i){
		
		if((samples[i].isValid)&&(samples[i].name==strName)){
			
			//found it
			//reset avg/min/max ONLY
			//because the sample may be running
			samples[i].maxPc=samples[i].minPc=-1;
			samples[i].dataCount=0;
			return;
		}
	}
}	

void ProfileSample::resetAll(){
	
	for(int i=0;i<MAX_PROFILER_SAMPLES;++i){
		
		if(samples[i].isValid){
			samples[i].maxPc=samples[i].minPc=-1;
			samples[i].dataCount=0;
		}
	}
}