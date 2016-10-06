#include "stdafx.h"
#include "GameManager.h"

#include <Windows.h>


GameManager::GameManager()
{
	this->screen = Screen();
}

GameManager::~GameManager()
{
}

void GameManager::updateTargets()
{
	for(Target target : this->targets)
	{
		target.update();
		this->displayTargets();
	}
}

void GameManager::spawnTarget(int x, int y)
{
	Position position;
	position.x = x;
	position.y = y;
	this->addTarget(Target(position));
}

void GameManager::addTarget(Target target)
{
	this->targets.push_back(target);
}

void GameManager::removeTarget(Target target)
{
	// TODO
}

Screen* GameManager::getScreenManager() {
	return &(this->screen);
}

void GameManager::displayTargets() {
	for (Target target : this->targets) {
		screen.buffer[target.position.y][target.position.x].Char.AsciiChar = '*';
		screen.buffer[target.position.y][target.position.x].Attributes = FOREGROUND_GREEN | FOREGROUND_RED;
	}
	// screen.buffer[player.position.y + k][player.position.x + l].Attributes = FOREGROUND_YELLOW;
}