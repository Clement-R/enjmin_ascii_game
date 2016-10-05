#pragma once

#include <windows.h>

const int SCREEN_WIDTH = 120;
const int SCREEN_HEIGHT = 30;

class Screen
{
	public:
		HANDLE hOutput;
		COORD dwBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
		COORD dwBufferCoord = { 0, 0 };
		SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
		CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

		Screen();
		~Screen();

		void read();
		void display();
};

