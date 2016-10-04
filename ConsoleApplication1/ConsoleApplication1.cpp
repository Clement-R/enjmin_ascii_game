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
	
	// Movement variables related
	int counter = 0;
	int lastKey = 0x00;
	
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
	
	int coordXStart = 0;
	int coordYStart = 0;
	
	struct position {
		int x;
		int y;
	};

	position playerPosition;
	playerPosition.x = coordXStart;
	playerPosition.y = coordYStart;

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
					buffer[playerPosition.y + k][playerPosition.x + l].Char.AsciiChar = playerSprite[k][l];
					buffer[playerPosition.y + k][playerPosition.x + l].Attributes = FOREGROUND_GREEN;
					// buffer[0 + k][0 + l].Char.AsciiChar = player_sprite[k][l];
				}
			}

			WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

			if (GetKeyState(VK_DOWN) < 0) {
				if (lastKey == VK_DOWN) {
					counter++;
				}
				else {
					counter = 1;
					lastKey = VK_DOWN;
				}
			}

			if (GetKeyState(VK_UP) < 0) {
				if (lastKey == VK_UP) {
					counter++;
				}
				else {
					counter = 1;
					lastKey = VK_UP;
				}
			}

			if (GetKeyState(VK_RIGHT) < 0) {
				if (lastKey == VK_RIGHT) {
					counter++;
				}
				else {
					counter = 1;
					lastKey = VK_RIGHT;
				}
			}

			if (GetKeyState(VK_LEFT) < 0) {
				if (lastKey == VK_LEFT) {
					counter++;
				}
				else {
					counter = 1;
					lastKey = VK_LEFT;
				}
			}
			
			// Counter : 30 means almost 1pixel/s, 15 means 1pixel/0.5s, 8 1pixel/0.25s
			if (counter == 4) {

				if (lastKey == VK_RIGHT) {
					playerPosition.x += 2;
				}

				if (lastKey == VK_LEFT) {
					playerPosition.x -= 2;
				}

				if (lastKey == VK_UP) {
					playerPosition.y--;
				}

				// Check player collision with the ground, if so we stop him
				if (lastKey == VK_DOWN && (playerPosition.y + 1 + playerHeight) <= SCREEN_HEIGHT) {
					playerPosition.y++;
				}

				
				// playerPosition[0] ++;

				counter = 0;
			}

			elapsed = nyt->getElapsedMs(true);
		}
	}

	return 0;
}
