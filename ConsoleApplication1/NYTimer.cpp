#include "stdafx.h"
#include "NYTimer.h"




NYTimer::NYTimer()
{
	QueryPerformanceCounter(&lastUpdateTime);
	LARGE_INTEGER li_freq;
	QueryPerformanceFrequency(&li_freq);
	freq = li_freq.QuadPart;
	freq /= 1000;
}

void NYTimer::start(void)
{
	QueryPerformanceCounter(&lastUpdateTime);
}

float NYTimer::getElapsedSeconds(bool restart = false)
{
	LARGE_INTEGER timeNow;
	QueryPerformanceCounter(&timeNow);
	LONGLONG elapsedLong = timeNow.QuadPart - lastUpdateTime.QuadPart;

	float elapsed = (float)((float)elapsedLong / (float)freq);
	elapsed /= 1000.0f;

	if (restart)
		lastUpdateTime = timeNow;

	return elapsed;
}

unsigned long NYTimer::getElapsedMs(bool restart = false)
{
	LARGE_INTEGER timeNow;
	QueryPerformanceCounter(&timeNow);
	LONGLONG elapsedLong = timeNow.QuadPart - lastUpdateTime.QuadPart;

	unsigned long elapsed = (unsigned long)((float)elapsedLong / (float)freq);

	if (restart)
		lastUpdateTime = timeNow;
	return elapsed;
}