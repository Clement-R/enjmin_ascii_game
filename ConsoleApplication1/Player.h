#pragma once

#include "Entity.h"
#include "Position.h"

class Player : public Entity
{
	public:
		int score = 0;
		static const int PLAYER_WIDTH= 9;
		static const int PLAYER_HEIGHT = 3;

		char playerSprite[PLAYER_HEIGHT][PLAYER_WIDTH];
		char playerAnimation[8][9];
		int frameCounter = 0;
		Position position;
		int playerXSpeed = 4;
		int playerYSpeed = 4;
		bool isOnFloor = false;
		int currentFrame = 0;
		Player();
		Player(int life);
		Player(int life, Position postion);
		~Player();

		void update();
		void move(int x, int y);
		void loadAnimation();
	private:
		int life;
};

