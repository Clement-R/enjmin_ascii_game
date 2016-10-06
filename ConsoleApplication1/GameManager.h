#pragma once

#include <list>
#include "Player.h"
#include "Position.h"
#include "Screen.h"
#include "Target.h"

using namespace std;

class GameManager
{
public:
	static const int minTargetSpawnY = 0;
	static const int maxTargetSpawnY = 25;
	GameManager();
	~GameManager();

	void updateTargets();

	void spawnTarget(int x, int y);
	void addTarget(Target * target);
	Screen* getScreenManager();
	Player* getPlayer();
	void displayTargets();

private:
	list<Target*> targets;
	Screen screen;
};
