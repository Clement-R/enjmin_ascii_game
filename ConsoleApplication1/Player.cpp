#include "stdafx.h"
#include "Player.h"


Player::Player(int life)
{
	// TODO : load sprite from external file
	// this->playerSprite;
	this->life = life;
	this->playerPosition.x = 0;
	this->playerPosition.y = 0;
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