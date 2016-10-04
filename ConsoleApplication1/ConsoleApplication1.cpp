// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>

#include "NYTimer.h"

#define WIN32_LEAN_AND_MEAN
#define SCREEN_WIDTH	240
#define SCREEN_HEIGHT	 30
#define MS_PER_UPDATE    32

/*
const int CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE;
const int PURPLE = FOREGROUND_BLUE | FOREGROUND_RED;
const int YELLOW = FOREGROUND_GREEN | FOREGROUND_RED;
const int WHITE = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
const int PINK = PURPLE | FOREGROUND_INTENSITY;
*/

#define CYAN     FOREGROUND_GREEN | FOREGROUND_BLUE
#define PURPLE   FOREGROUND_BLUE | FOREGROUND_RED
#define YELLOW   FOREGROUND_GREEN | FOREGROUND_RED
#define WHITE    FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED
#define PINK     PURPLE | FOREGROUND_INTENSITY

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	NYTimer* nyt =  new NYTimer();
	
	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	/*
	ReadConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
	buffer[5][10].Char.AsciiChar = 'H';
	buffer[5][10].Attributes = 0x0E;
	WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);
	*/
	
	int counter = 0;
	int coordXStart = 0;
	int coordYStart = 0;
	
	const char playerSprite[3][9] = {
		{'_', '_', '_', '.', '_', '_', '_', ' ', ' ' },
		{' ', ' ', '(', '_', ']', '=', '=', '=', '*' },
		{' ', ' ', 'o', ' ', '0', ' ', ' ', ' ', ' '}
		/*{ '-', '-', '-', '-', '-' },
		{ ' ', ' ', '|', ' ', ' ' },
		{ '*', '*', '*', '*', '*' },
		{ '*', '*', '*', '*', '*' }*/
	};
	const int playerHeight = sizeof(playerSprite) / sizeof(playerSprite[0]);
	const int playerWidth = sizeof(playerSprite[0]);
	// playerPosition[0] : X, playerPosition[1] : Y, 
	int playerPosition[2] = { coordXStart, coordYStart };

	double elapsed = 0;

	while (true){
		elapsed = nyt->getElapsedMs(false);

		if (elapsed > MS_PER_UPDATE){
			ReadConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

			for (int i = 0; i < SCREEN_HEIGHT; i++)
			{
				for (int j = 0; j < SCREEN_WIDTH; j++)
				{
					if (j % 2 == 0) {
						buffer[i][j].Char.AsciiChar = '0';
					}
					else {
						buffer[i][j].Char.AsciiChar = '1';
					}
					buffer[i][j].Attributes = WHITE;
				}
			}

			// Sizeof returns 12 if array is like : [3][4], to avoid that we use a dirty trick
			for (int k = 0; k < playerHeight; k++)
			{
				for (int l = 0; l < playerWidth; l++)
				{
					// buffer[0 + k][coordXStart + l].Char.AsciiChar = player_sprite[k][l];
					buffer[playerPosition[1] + k][playerPosition[0] + l].Char.AsciiChar = playerSprite[k][l];
					buffer[playerPosition[1] + k][playerPosition[0] + l].Attributes = FOREGROUND_GREEN;
					// buffer[0 + k][0 + l].Char.AsciiChar = player_sprite[k][l];
				}
			}

			WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

			if (GetKeyState(VK_DOWN) < 0) {
				counter++;
			}
			
			// Counter : 30 means almost 1pixel/s, 15 means 1pixel/0.5s, 8 1pixel/0.25s
			if (counter == 4) {

				// Check player collision with the ground, if so we stop him
				if ((playerPosition[1] + 1 + playerHeight) <= SCREEN_HEIGHT) {
					// TODO : Use user-input to manage movement
					// Make the player move of one tile on Y axis
					playerPosition[1] ++;
				}
				// END of player collision with the ground
				
				// playerPosition[0] ++;

				counter = 0;
			}

			elapsed = nyt->getElapsedMs(true);
		}
	}

	return 0;
}
