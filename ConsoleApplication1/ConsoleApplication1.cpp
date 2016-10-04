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
#define MAP_WIDTH       480

#define MS_PER_UPDATE    32

#define PLAYER_X_SPEED    4
#define PLAYER_Y_SPEED    1

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

// Custom structures used in the game
struct position {
	int x;
	int y;
};

void drawMap(char map[][MAP_WIDTH], CHAR_INFO (&buffer)[SCREEN_HEIGHT][SCREEN_WIDTH], position cameraPosition) {
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			buffer[i][j].Char.AsciiChar = map[i][j + cameraPosition.x];
			buffer[i][j].Attributes = WHITE;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Initialize a new timer
	NYTimer* nyt =  new NYTimer();
	
	// Initialize buffer that's going to be drawn
	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	
	// Movement variables related
	int frameCounter = 0;
	int lastKey = 0x00;
	
	// Sprites
	const char playerSprite[3][9] = {
		{'_', '_', '_', '.', '_', '_', '_', ' ', ' ' },
		{' ', ' ', '(', '_', ']', '=', '=', '=', '*' },
		{' ', ' ', 'o', ' ', '0', ' ', ' ', ' ', ' '}
	};

	// Maps
	char map1[SCREEN_HEIGHT][MAP_WIDTH];
	int mapWidthCounter = 0;
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (j % 2 == 0) {
				map1[i][j] = '0';
			}
			else {
				map1[i][j] = '1';
			}
			
		}
	}

	// Players informations
	const int playerHeight = sizeof(playerSprite) / sizeof(playerSprite[0]);
	const int playerWidth = sizeof(playerSprite[0]);
	
	int coordXStart = 0;
	int coordYStart = 0;
	
	position playerPosition;
	playerPosition.x = coordXStart;
	playerPosition.y = coordYStart;

	// Camera informations
	position cameraPosition;
	cameraPosition.x = 0;
	cameraPosition.y = 0;

	// Game loop
	double elapsed = 0;
	while (true){
		elapsed = nyt->getElapsedMs(false);

		// Check if one frame time has passed, we update the game 30FPS
		if (elapsed > MS_PER_UPDATE){
			ReadConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

			drawMap(map1, buffer, cameraPosition);

			// Draw player
			for (int k = 0; k < playerHeight; k++)
			{
				for (int l = 0; l < playerWidth; l++)
				{
					buffer[playerPosition.y + k][playerPosition.x + l].Char.AsciiChar = playerSprite[k][l];
					buffer[playerPosition.y + k][playerPosition.x + l].Attributes = FOREGROUND_GREEN;
				}
			}

			WriteConsoleOutput(hOutput, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion);

			// Manage keyboard events, if a pkey is pressed we increase the counter and after
			// a number of events we move the player accordingly
			if (GetKeyState(VK_DOWN) < 0) {
				if (lastKey == VK_DOWN) {
					frameCounter++;
				}
				else {
					frameCounter = 1;
					lastKey = VK_DOWN;
				}
			}

			if (GetKeyState(VK_UP) < 0) {
				if (lastKey == VK_UP) {
					frameCounter++;
				}
				else {
					frameCounter = 1;
					lastKey = VK_UP;
				}
			}

			if (GetKeyState(VK_RIGHT) < 0) {
				if (lastKey == VK_RIGHT) {
					frameCounter++;
				}
				else {
					frameCounter = 1;
					lastKey = VK_RIGHT;
				}
			}

			if (GetKeyState(VK_LEFT) < 0) {
				if (lastKey == VK_LEFT) {
					frameCounter++;
				}
				else {
					frameCounter = 1;
					lastKey = VK_LEFT;
				}
			}
			
			// Counter : 30 means almost 1pixel/s, 15 means 1pixel/0.5s, 8 1pixel/0.25s
			if (frameCounter == 4) {

				if (lastKey == VK_RIGHT && (playerPosition.x + PLAYER_X_SPEED) <= MAP_WIDTH) {
					playerPosition.x += PLAYER_X_SPEED;
					cameraPosition.x += PLAYER_X_SPEED;
				}

				if (lastKey == VK_LEFT && (playerPosition.x - PLAYER_X_SPEED) >= 0) {
					playerPosition.x -= PLAYER_X_SPEED;
					cameraPosition.x -= PLAYER_X_SPEED;
				}

				if (lastKey == VK_UP && (playerPosition.y - PLAYER_Y_SPEED) >= 0) {
					playerPosition.y -= PLAYER_Y_SPEED;
				}

				// Check player collision with the ground, if so we stop him
				if (lastKey == VK_DOWN && (playerPosition.y + PLAYER_Y_SPEED + playerHeight) <= SCREEN_HEIGHT) {
					playerPosition.y += PLAYER_Y_SPEED;
				}

				// DEBUG
				OutputDebugStringA(to_string(cameraPosition.x).c_str());
				OutputDebugStringA("\n");
				// ENDOF DEBUG

				frameCounter = 0;
			}

			elapsed = nyt->getElapsedMs(true);
		}
	}

	return 0;
}