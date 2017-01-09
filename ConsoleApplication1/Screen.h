#pragma once

#include <windows.h>
#include <iostream>

using namespace std;

class Screen
{
	public:
		static const int SCREEN_WIDTH = 90;
		static const int SCREEN_HEIGHT = 32;

		HANDLE hOutput;
		COORD dwBufferSize;
		COORD dwBufferCoord;
		SMALL_RECT rcRegion;
		CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

		Screen();
		~Screen();

		void read();
		void display();
		void displayScore(string header, int score);
};
