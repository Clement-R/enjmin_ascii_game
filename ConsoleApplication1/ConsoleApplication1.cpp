// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define SCREEN_WIDTH	240
#include <iostream>
#include "NYTimer.h"
#include <string>
#include <chrono>
#include <thread>
#define SCREEN_HEIGHT	120
using namespace std;

double elapsed = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	NYTimer* nyt =  new NYTimer();
	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	string message = "Hello world its time to die...";
	COORD dwBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	ReadConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	buffer[5][10].Char.AsciiChar = 'H';
	buffer[5][10].Attributes = 0x0E;
	buffer[5][11].Char.AsciiChar = 'i';
	buffer[5][11].Attributes = 0x0B;
	buffer[5][12].Char.AsciiChar = '!';
	buffer[5][12].Attributes = 0x0A;

	WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
	string str;
	/*for (int i = 0; i < 10;i++){
		cout << nyt->getElapsedMs(false)<<endl;
	}*/
	
	int counter = 0;
	int coorXStart = 10;
	int coorYStart = 5;
	int i = 0;
	int color = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED;
	while (true){
		elapsed = nyt->getElapsedMs(false);

		if (elapsed > 32){
			//cout << elapsed << endl;
			ReadConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
				dwBufferCoord, &rcRegion);

			buffer[coorYStart][coorXStart].Char.AsciiChar = message[i];
			buffer[coorYStart][coorXStart].Attributes = color;
			coorXStart++;
			WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize,
				dwBufferCoord, &rcRegion);
			
			if (i + 1 > message.size()){
				i = 0;
				coorYStart++;
				coorXStart = 10;
				color = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | BACKGROUND_RED;
			} else{
				i++;
			}
			
			elapsed = nyt->getElapsedMs(true);
		}
	}
	
	cin >> str;
	return 0;
}

