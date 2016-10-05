#include "stdafx.h"
#include "Player.h"
#include "Screen.h"
#include <fstream>

using namespace std;

Player::Player(int life)
{
	char data[29];
	ifstream is("player_sprite");
	
	int position = 0;
	while (!is.eof())
	{
		//reading one character from file to array
		is.get(data[position]);
		position++;
	}

	int counter = 0;
	for (int i = 0; i < this->PLAYER_HEIGHT; i++)
	{
		for (int j = 0; j < this->PLAYER_WIDTH; j++)
		{
			if (data[counter] != '\n') {
				this->playerSprite[i][j] = data[counter];
			}
			counter++;
		}
	}

	this->life = life;
	this->playerPosition.x = 15;
	this->playerPosition.y = 0;

	this->playerPosition.x = this->PLAYER_WIDTH;
	this->playerPosition.y = Screen::SCREEN_HEIGHT/2;
}


Player::Player(int life, int x, int y)
{
	this->life = life;
	this->playerPosition.x = x;
	this->playerPosition.y = y;
}


Player::~Player()
{
}

void Player::update() {
}

void Player::move(int x, int y) {
}