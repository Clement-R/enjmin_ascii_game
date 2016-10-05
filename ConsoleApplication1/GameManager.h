#pragma once

#include <vector>
#include "Target.h"
#include "Position.h"
#include "Screen.h"

using namespace std;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void updateTargets();

	void spawnTarget(int x, int y);
	void addTarget(Target target);
	void removeTarget(Target target);

	Screen getScreenManager();

private:
	vector<Target> targets;
	Screen screen;
};
