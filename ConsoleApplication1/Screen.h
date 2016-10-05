#pragma once

#include <windows.h>

class Screen
{
	public:
		static const int SCREEN_WIDTH = 120;
		static const int SCREEN_HEIGHT = 30;

		HANDLE hOutput;
		COORD dwBufferSize;
		COORD dwBufferCoord;
		SMALL_RECT rcRegion;
		CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

		Screen();
		~Screen();

		void read();
		void display();
};

