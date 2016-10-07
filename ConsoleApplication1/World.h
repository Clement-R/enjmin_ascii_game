#pragma once
#include "Entity.h"
#include "Screen.h"
class World : public Entity
{
public:

	int gravity = 1;
	int mapIndex = 0;
	
	static const int MAP_WIDTH = 200;
	static const int MAP_HEIGHT = 32;

	char map[MAP_HEIGHT][MAP_WIDTH];
	char previousMap[MAP_HEIGHT][MAP_WIDTH];

	char (*currentMap)[MAP_WIDTH];
	void update();
	void draw(CHAR_INFO(&buffer)[Screen::SCREEN_HEIGHT][Screen::SCREEN_WIDTH]);
	World();
	~World();
};

