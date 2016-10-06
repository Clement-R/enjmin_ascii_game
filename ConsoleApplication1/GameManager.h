#pragma once

#include <list>
#include "Target.h"
#include "Position.h"
#include "Screen.h"

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
	void displayTargets();

private:
	list<Target*> targets;
	Screen screen;
};
