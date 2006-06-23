#ifndef PROFILER_H_
#define PROFILER_H_

#include <string>
#include <SDL/SDL.h>

#define MAX_PROFILER_SAMPLES 50

class ProfilerOutputHandler;
class ProfileSample;

class ProfileSample{
	
	public:
		ProfileSample(std::string sampleName);
		~ProfileSample();

		static void output();

		static void resetSample(std::string sampleName);
		static void resetAll();

		static ProfilerOutputHandler *outputHandler;

		static bool isRunning;

	protected:
		//index into the array of samples
		int sampleIndex;
		int parentIndex;

		inline float getTime(){ return ((float)SDL_GetTicks())/1000.0f; }

		static struct profileSample{
			
			profileSample(){
				isValid=false; 
				dataCount=0;
				averagePc=minPc=maxPc=-1;
			}

			bool isValid;		//whether or not this sample is valid (for use with fixed-size arrays)
			bool isOpen;		//is this sample currently being profiled?
			unsigned int callCount;	//number of times this sample has been profiled this frame
			std::string name;	//name of the sample
		
			float startTime;	//starting time on the clock, in seconds
			float totalTime;	//total time recorded across all profiles of this sample
			float childTime;	//total time taken by children of this sample

			int parentCount;	//number of parents this sample has (useful for indenting)

			float averagePc;	//average percentage of game loop time taken up
			float minPc;		//minimum percentage of game loop time taken up
			float maxPc;		//maximum percentage of game loop time taken up
			unsigned long dataCount;//number of percentage values that have been stored
		} samples[MAX_PROFILER_SAMPLES];
		
	static int lastOpenedSample;
	static int openSampleCount;
	static float rootBegin, rootEnd;
};

class ProfilerOutputHandler{
	
	public:
		virtual void beginOutput(float tTotal)=0;
		virtual void sample(float fMin, float fAvg, float fMax, float tAvg, int callCount, std::string name, int parentCount)=0;
		virtual void endOutput()=0;
};

#ifdef _DEBUG
#define PROFILE(name) ProfileSample _profile_sample(name);
#else
#define PROFILE(name)
#endif

#endif /*PROFILER_H_*/
