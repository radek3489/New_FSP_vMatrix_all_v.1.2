#include "stdafx.h"
#include "Time_countner.h"


Time_countner::Time_countner()
{
	QueryPerformanceFrequency(&frequency);
}


Time_countner::~Time_countner()
{
}


void Time_countner::startTime()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	performanceCountStart = start;
}


void Time_countner::stopTime()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	performanceCountEnd = stop;
}


double Time_countner::getTime()
{
	return (performanceCountEnd.QuadPart - performanceCountStart.QuadPart)*1000.0 / frequency.QuadPart/1000.0;
}
