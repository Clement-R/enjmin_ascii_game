#include "stdafx.h"
#include "World.h"
#include <fstream>
#include "Screen.h"
#define WHITE    FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED
using namespace std;
World::World()
{
	//memset(this->map, 0, sizeof(this->map[0][0]) * World::MAP_WIDTH * World::MAP_HEIGHT);
	char data[10000];
	ifstream is("map_flat");
	int fileCursor = 0;
	while (!is.eof())
	{
		//reading one character from file to array
		is.get(data[fileCursor]);
		fileCursor++;
	}

	int counter = 0;
	//this->map1[Screen::SCREEN_HEIGHT][World::MAP_WIDTH];
	for (int i = 0; i < Screen::SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < World::MAP_WIDTH; j++)
		{
			if (data[counter] != '\n') {
				char tile = (data[counter] == '0') ? ' ' : data[counter];
				this->map[i][j] = tile;
				this->previousMap[i][j] = tile;
			}
			counter++;
		}
	}
	this->currentMap = this->map;
}

void World::draw(CHAR_INFO(&buffer)[Screen::SCREEN_HEIGHT][Screen::SCREEN_WIDTH], Position cameraPosition){
	
	for (int k = 0; k < Screen::SCREEN_HEIGHT; k++)
	{
		for (int l = 0; l < Screen::SCREEN_WIDTH; l++)
		{

			char tile = ' ';
			if (l < Screen::SCREEN_WIDTH - 1) {
				// Copy previous frame
				tile = this->previousMap[k][l + 1];
			}
			else
			{
				// Add new column
				tile = this->map[k][this->mapIndex];
			}

			this->previousMap[k][l] = tile;
			buffer[k][l].Char.AsciiChar = tile;

			switch (tile)
			{
			case ' ':
				buffer[k][l].Attributes = FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
				break;

			case 'w':
				buffer[k][l].Attributes = WHITE | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN;
				break;

			default:
				buffer[k][l].Attributes = WHITE;
				break;
			}

		}
	}
}
World::~World()
{

}

void World::update() {
	if (this->mapIndex + 1 < World::MAP_WIDTH - 1) {
		++this->mapIndex;
	}
	else {
		this->mapIndex = 0;
	}
}