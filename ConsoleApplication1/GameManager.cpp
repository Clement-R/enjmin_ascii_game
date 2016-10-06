#include "stdafx.h"
#include "GameManager.h"

#include <Windows.h>
#include <algorithm>
#include <string>

using namespace std;

GameManager::GameManager()
{
	this->screen = Screen();
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

void GameManager::displayTargets() {
	for (Target *target : this->targets) {
		// Todo : create target sprite and display it here
		screen.buffer[target->position.y][target->position.x].Char.AsciiChar = '*';
		screen.buffer[target->position.y][target->position.x].Attributes = FOREGROUND_GREEN | FOREGROUND_RED;
	}
}

