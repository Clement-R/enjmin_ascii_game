#pragma once

#ifndef __NY_TIMER__
#define __NY_TIMER__

#include <windows.h>

class NYTimer
{
public:
	LARGE_INTEGER lastUpdateTime;
	LONGLONG freq;

	NYTimer();
	void start(void);
	float getElapsedSeconds(bool restart );
	unsigned long getElapsedMs(bool restart);
	~NYTimer();
};

#endif
