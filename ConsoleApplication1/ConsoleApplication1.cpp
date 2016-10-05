// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>

#include "NYTimer.h"
#include "Player.h"
#include "Position.h"
#include "Screen.h"
#include "World.h"
#define WIN32_LEAN_AND_MEAN

#define MAP_WIDTH       480

#define MS_PER_UPDATE    30

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

void drawMap(char map[][MAP_WIDTH], CHAR_INFO (&buffer)[Screen::SCREEN_HEIGHT][Screen::SCREEN_WIDTH], Position cameraPosition) {
	for (int i = 0; i < Screen::SCREEN_HEIGHT; i++)
	{
	for (int j = 0; j < Screen::SCREEN_WIDTH; j++)
	{
		buffer[i][j].Char.AsciiChar = map[i][j + cameraPosition.x];
		buffer[i][j].Attributes = WHITE;
	}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Initialize a new timer
	NYTimer* nyt = new NYTimer();

	// Initialize screen
	Screen screen = Screen();

	// Initialize player
	Player player = Player(5);

	// Initialize World
	World world =  World();
	// Movement variables related
	int frameCounter = 0;
	int gameCounter = 0;
	int lastKey = 0x00;

	// Maps
	char map1[screen.SCREEN_HEIGHT][MAP_WIDTH];
	int mapWidthCounter = 0;
	for (int i = 0; i < screen.SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			map1[i][j] = ' ';
		}
	}

	// Players informations
	const int playerHeight = sizeof(player.playerSprite) / sizeof(player.playerSprite[0]);
	const int playerWidth = sizeof(player.playerSprite[0]);

	// Camera informations
	Position cameraPosition;
	cameraPosition.x = player.position.x;
	cameraPosition.y = player.position.y;

	// Game loop
	double elapsed = 0;
	while (true) {
		elapsed = nyt->getElapsedMs(false);

		// Check if one frame time has passed, we update the game 30FPS
		if (elapsed > MS_PER_UPDATE) {
			screen.read();

			drawMap(map1, screen.buffer, cameraPosition);

			// Death condition
			if ((player.position.y + player.playerYSpeed) > Screen::SCREEN_HEIGHT) {
				// Stop the game
				break;
			}

			// Draw player
			for (int k = 0; k < playerHeight; k++)
			{
				for (int l = 0; l < playerWidth; l++)
				{
					screen.buffer[player.position.y + k][player.position.x + l].Char.AsciiChar = player.playerSprite[k][l];
					screen.buffer[player.position.y + k][player.position.x + l].Attributes = FOREGROUND_GREEN;
				}
			}

			screen.display();

			// Manage keyboard events, if a key is pressed we increase the counter and after
			// a number of events we move the player accordingly
			if (GetKeyState(VK_SPACE) < 0) {
				if (lastKey == VK_SPACE) {
					frameCounter++;
				}
				else {
					frameCounter = 1;
					lastKey = VK_SPACE;
				}
			}

			// frameCounter : 30 means almost 1pixel/s, 15 means 1pixel/0.5s, 8 1pixel/0.25s
			if (frameCounter == 4) {

				if (lastKey == VK_SPACE && (player.position.y - player.playerYSpeed) >= 0) {
					player.position.y -= player.playerYSpeed * 2;
				}

				// DEBUG
				/*
				OutputDebugStringA(to_string(player.playerPosition.x).c_str());
				OutputDebugStringA("\n");
				*/
				// ENDOF DEBUG

				frameCounter = 0;
				//lastKey = 0;
			}

			if (gameCounter % 6 == 0) {
				// player.playerPosition.y += world.gravity;
				player.position.y += player.playerYSpeed / 2;
				if ((player.position.y + playerHeight) >= screen.SCREEN_HEIGHT)
					player.isOnFloor = true;
			}

			if (player.position.y <= 0) {
				player.position.y = 0;
			}

			++gameCounter;
			elapsed = nyt->getElapsedMs(true);
		}
	}

	// wait the player to push SPACEBAR to 
	while ((GetKeyState(VK_SPACE) == 0)) {
	}

	return 0;
}