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
	int difficulty = 120;

	GameManager();
	void initialize();
	~GameManager();

	void updateTargets();
	void checkCollisions();

	void increaseDifficulty(int lastFrame);

	void spawnTarget(int x, int y);
	void addTarget(Target * target);
	
	Screen* getScreenManager();
	Player* getPlayer();

	void displayTargets();

	int getScore();

	int getHighscore();

	void setHighscore(int score);

	string xor_score(string score);

private:
	list<Target*> targets;
	Screen screen;
	Player player;
	int score;
	char key;
};
