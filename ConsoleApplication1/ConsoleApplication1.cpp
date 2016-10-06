// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
#include <string>
#include <time.h>
#include <windows.h>

#include "GameManager.h"
#include "NYTimer.h"
#include "Player.h"
#include "Position.h"
#include "Screen.h"
#include "Target.h"
#include "World.h"

#define WIN32_LEAN_AND_MEAN

#define MAP_WIDTH       480


using namespace std;

void drawMap(char map[][MAP_WIDTH], CHAR_INFO (&buffer)[Screen::SCREEN_HEIGHT][Screen::SCREEN_WIDTH], Position cameraPosition) {
	for (int i = 0; i < Screen::SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < Screen::SCREEN_WIDTH; j++)
		{
			buffer[i][j].Char.AsciiChar = map[i][j + cameraPosition.x];
			buffer[i][j].Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int MS_PER_UPDATE = 30;
	
	const int CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE;
	const int PURPLE = FOREGROUND_BLUE | FOREGROUND_RED;
	const int YELLOW = FOREGROUND_GREEN | FOREGROUND_RED;
	const int WHITE = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
	const int PINK = PURPLE | FOREGROUND_INTENSITY;

	// Initialize game
	GameManager gameManager = GameManager();
	Screen *screen = gameManager.getScreenManager();
	Player *player = gameManager.getPlayer(); 
	
	// Initialize a new timer
	NYTimer* nyt = new NYTimer();

	// Initialize player
	
	// Initialize World
	World world =  World();

	// Initialize random number generator with random seed
	srand(time(NULL));
	int randomPosition = 0;

	// Movement variables related
	int frameCounter = 0;
	int gameCounter = 0;
	int lastKey = 0x00;

	// Maps
	char map1[Screen::SCREEN_HEIGHT][MAP_WIDTH];
	int mapWidthCounter = 0;
	for (int i = 0; i < Screen::SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			map1[i][j] = ' ';
		}
	}

	// Camera informations
	Position cameraPosition;
	cameraPosition.x = player->position.x;
	cameraPosition.y = player->position.y;

	// Game loop
	double elapsed = 0;
	while (true)
	{
		elapsed = nyt->getElapsedMs(false);

		// Check if one frame time has passed, we update the game 30FPS
		if (elapsed > MS_PER_UPDATE)
		{
			screen->read();
			
			drawMap(map1, screen->buffer, cameraPosition);

			// Death condition
			if ((player->position.y + player->playerYSpeed) > Screen::SCREEN_HEIGHT)
			{
				// Stop the game
				break;
			}

			// Draw player
			for (int k = 0; k < Player::PLAYER_HEIGHT; k++)
			{
				for (int l = 0; l < Player::PLAYER_WIDTH; l++)
				{
					screen->buffer[player->position.y + k][player->position.x + l].Char.AsciiChar = player->playerSprite[k][l];
					screen->buffer[player->position.y + k][player->position.x + l].Attributes = FOREGROUND_GREEN;
				}
			}

			// Manage keyboard events, if a key is pressed we increase the counter and after
			// a number of events we move the player accordingly
			if (GetKeyState(VK_SPACE) < 0)
			{
				if (lastKey == VK_SPACE)
				{
					frameCounter++;
				}
				else
				{
					frameCounter = 1;
					lastKey = VK_SPACE;
				}
			}

			// frameCounter : 30frames = 1s
			if (frameCounter == 3)
			{

				if (lastKey == VK_SPACE && (player->position.y - player->playerYSpeed) >= 0)
				{
					player->position.y -= player->playerYSpeed * 2;
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

			if (gameCounter % 6 == 0)
			{
				// player.playerPosition.y += world.gravity;
				player->position.y += player->playerYSpeed / 2;
				if ((player->position.y + Player::PLAYER_HEIGHT) >= Screen::SCREEN_HEIGHT)
					player->isOnFloor = true;
			}

			if (gameCounter % 120 == 0 || gameCounter == 0)
			{
				// Choose random position
				randomPosition = rand() % GameManager::maxTargetSpawnY + GameManager::minTargetSpawnY;

				// Spawn the target
				gameManager.spawnTarget(70, randomPosition);
			}

			if (player->position.y <= 0)
			{
				player->position.y = 0;
			}

			gameManager.updateTargets();

			screen->display();
			++gameCounter;
			elapsed = nyt->getElapsedMs(true);
		}
	}

	// wait the player to push down arrow key to stop the program
	while ((GetKeyState(VK_DOWN) == 0)) {}

	return 0;
}

