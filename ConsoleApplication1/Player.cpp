#include "stdafx.h"
#include "Player.h"
#include "Screen.h"
#include <fstream>

using namespace std;

Player::Player() {}

Player::Player(int life)
{
	char data[29];
	ifstream is("player_sprite");
	
	int fileCursor = 0;
	while (!is.eof())
	{
		//reading one character from file to array
		is.get(data[fileCursor]);
		fileCursor++;
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
	this->position.x = 0;
	this->position.y = 0;

	this->position.x = this->PLAYER_WIDTH;
	this->position.y = Screen::SCREEN_HEIGHT/2;
	loadAnimation();
}


Player::Player(int life, Position position)
{
	this->life = life;
	this->position = position;
}


Player::~Player()
{
}
void Player::loadAnimation(){
	char data[81];
	ifstream is("player_animation");
	int fileCursor = 0;
	int counter = 0;
	while (!is.eof())
	{
		//reading one character from file to array
		is.get(data[fileCursor]);
		fileCursor++;
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 9; j++)
		{
 			if (data[counter] != '\n') {
				this->playerAnimation[i][j] = data[counter];
			}
			counter++;
		}
	}
}
void Player::update() {
	if (frameCounter > 3){
		for (int i = 0; i < 10; i++)
		{
			playerSprite[0][i] = this->playerAnimation[currentFrame][i];
		}
		currentFrame++;
		if (currentFrame > 7)
			currentFrame = 0;
		frameCounter = 0;
	}
	else {
		frameCounter++;
	}
	
}

void Player::move(int x, int y) {
}