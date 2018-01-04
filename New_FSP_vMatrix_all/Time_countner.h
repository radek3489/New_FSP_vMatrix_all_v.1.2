#pragma once
class Time_countner
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER performanceCountStart;
	LARGE_INTEGER performanceCountEnd;
public:
	Time_countner();
	~Time_countner();
	void startTime();
	void stopTime();
	double getTime();
};

