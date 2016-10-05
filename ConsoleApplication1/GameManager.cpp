#include "stdafx.h"
#include "GameManager.h"


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

Screen GameManager::getScreenManager() {
	return this->screen;
}