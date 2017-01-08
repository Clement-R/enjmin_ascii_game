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

void drawMap(char map[][MAP_WIDTH], CHAR_INFO (&buffer)[Screen::SCREEN_HEIGHT][Screen::SCREEN_WIDTH], Position cameraPosition)
{
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

	// Initialize World
	World world = World();

	// Initialize random number generator with random seed
	srand(time(NULL));
	int randomPosition = 0;

	// Movement variables related
	int frameCounter = 0;
	int gameCounter = 0;
	int lastKey = 0x00;

	double elapsed = 0;
	bool isGameInitialized = true;

	// Game loop
	while (true)
	{
		if (!isGameInitialized)
		{
			// Initialize game
			gameManager.initialize();
			screen = gameManager.getScreenManager();
			player = gameManager.getPlayer();
			// Initialize a new timer
			nyt = new NYTimer();

			// Initialize World
			world = World();

			// Initialize random number generator with random seed
			srand(time(NULL));
			randomPosition = 0;

			// Movement variables related
			frameCounter = 0;
			gameCounter = 0;
			lastKey = 0x00;

			elapsed = 0;

			isGameInitialized = true;
		}
		else
		{
			elapsed = nyt->getElapsedMs(false);

			// Check if one frame time has passed, we update the game 30FPS
			if (elapsed > MS_PER_UPDATE)
			{
				screen->read();

				world.draw(screen->buffer);

				// Death condition
				if ((player->position.y + player->playerYSpeed) > Screen::SCREEN_HEIGHT)
				{
					OutputDebugStringA(to_string(GetKeyState(0x52)).c_str());
					OutputDebugStringA("\n");

					// Check if it's a new highscore
					if (gameManager.getScore() > gameManager.getHighscore())
					{
						gameManager.setHighscore(gameManager.getScore());
					}

					// Prepare for restart
					isGameInitialized = false;

					bool exit = false;

					// Show restart instruction
					string text = "Restart [R]";
					int x = 35;
					int y = 15;
					for (size_t i = 0; i < text.length(); i++)
					{
						screen->buffer[y][x].Char.AsciiChar = (char) text[i];
						screen->buffer[y][x].Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
						x++;
					}

					// Show score
					// TODO

					screen->display();

					// Wait the player to push R key to restart the game
					// 0x52 = R key
					while (!exit)
					{
						if(GetKeyState(0x52) < 0)
						{
							exit = true;
						}
					}
				}

				// Draw player
				for (int k = 0; k < Player::PLAYER_HEIGHT; k++)
				{
					for (int l = 0; l < Player::PLAYER_WIDTH; l++)
					{
						screen->buffer[player->position.y + k][player->position.x + l].Char.AsciiChar = player->playerSprite[k][l];
						screen->buffer[player->position.y + k][player->position.x + l].Attributes = WHITE | screen->buffer[player->position.y + k][player->position.x + l].Attributes;
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

				// frameCounter : 30FPS
				if (frameCounter == 3)
				{

					if (lastKey == VK_SPACE && (player->position.y - player->playerYSpeed) >= 0)
					{
						player->position.y -= player->playerYSpeed * 2;
					}

					frameCounter = 0;
				}

				if (gameCounter % 6 == 0)
				{
					player->position.y += player->playerYSpeed / 2;
					if ((player->position.y + Player::PLAYER_HEIGHT) >= Screen::SCREEN_HEIGHT)
						player->isOnFloor = true;
				}

				if (gameCounter % gameManager.difficulty == 0 || gameCounter == 0)
				{
					// Choose random position
					randomPosition = rand() % GameManager::maxTargetSpawnY + GameManager::minTargetSpawnY;

					// Spawn the target
					gameManager.spawnTarget(Screen::SCREEN_WIDTH - 1, randomPosition);
				}

				gameManager.increaseDifficulty(gameCounter);

				if (player->position.y <= 0)
				{
					player->position.y = 0;
				}

				screen->displayScore(gameManager.getScore());

				world.update();
				player->update();
				gameManager.updateTargets();
				gameManager.checkCollisions();

				screen->display();
				++gameCounter;
				elapsed = nyt->getElapsedMs(true);

				// DEBUG
				/*
				OutputDebugStringA(to_string(player.playerPosition.x).c_str());
				OutputDebugStringA("\n");
				*/
				// ENDOF DEBUG
			}

		}
	}

	return 0;
}
