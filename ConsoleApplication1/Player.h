#pragma once

#include "Entity.h"
#include "Position.h"

class Player : public Entity
{
public:
	const char playerSprite[3][9] = {
		{ '_', '_', '_', '.', '_', '_', '_', ' ', ' ' },
		{ ' ', ' ', '(', '_', ']', '=', '=', '=', '*' },
		{ ' ', ' ', 'o', ' ', '0', ' ', ' ', ' ', ' ' }
	};
	
	Position playerPosition;

	Player(int life);
	Player(int life, int x, int y);
	~Player();

	void update();
	void move(int x, int y);

private:
	int life;
};

