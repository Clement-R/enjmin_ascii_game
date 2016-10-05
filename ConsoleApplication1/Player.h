#pragma once

#include "Entity.h"
#include "Position.h"

class Player : public Entity
{
	public:
		static const int PLAYER_WIDTH= 9;
		static const int PLAYER_HEIGHT = 3;

		char playerSprite[PLAYER_HEIGHT][PLAYER_WIDTH];
		Position position;
		int playerXSpeed = 0;
		int playerYSpeed = 4;
		bool isOnFloor = false;

		Player(int life);
		Player(int life, int x, int y);
		~Player();

		void update();
		void move(int x, int y);

	private:
		int life;
};

