#include "stdafx.h"
#include <Windows.h>
#include <algorithm>
#include <string>

#include "GameManager.h"

using namespace std;

GameManager::GameManager()
{
	this->screen = Screen();
	this->player = Player(5);
}

GameManager::~GameManager()
{
}

void GameManager::updateTargets()
{
	for (list<Target*>::iterator itr = this->targets.begin(); itr != this->targets.end(); /*nothing*/)
	{
		// Update the target
		(*itr)->update();

		// If it must be destroyed we do so
		if ((*itr)->needDestroy()) {
			itr = this->targets.erase(itr);
		}
		else {
			++itr;
		}	
	}

	this->displayTargets();
}

void GameManager::spawnTarget(int x, int y)
{
	Position position;
	position.x = x;
	position.y = y;
	Target *target = new Target(position);
	this->addTarget(target);
}

void GameManager::addTarget(Target *target)
{
	this->targets.push_back(target);
}

Screen* GameManager::getScreenManager() {
	return &(this->screen);
}

Player * GameManager::getPlayer()
{
	return &(this->player);
}

void GameManager::displayTargets() {
	for (Target *target : this->targets) {
		// Todo : create target sprite and display it here
		for (int i = 0; i < Target::TARGET_HEIGHT; i++)
		{
			for (int j = 0; j < Target::TARGET_WIDTH; j++)
			{
				screen.buffer[target->position.y + i][target->position.x + j].Char.AsciiChar = '*';
				screen.buffer[target->position.y + i][target->position.x + j].Attributes = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
			}
		}
	}
}

void GameManager::checkCollisions() {
	for (Target *target : this->targets) {
		// Detect collision
		if (abs(player.position.x - target->position.x) * 2 < (Player::PLAYER_WIDTH + Target::TARGET_WIDTH)
			&& abs(player.position.y - target->position.y) * 2 < (Player::PLAYER_HEIGHT + Target::TARGET_HEIGHT))
		{
			target->setToDestroy();
		}
	}
}

