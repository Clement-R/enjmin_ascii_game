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
				this->map2[i][j] = tile;
			}
			counter++;
		}
	}
	this->currentMap = this->map;
}

void World::draw(CHAR_INFO(&buffer)[Screen::SCREEN_HEIGHT][Screen::SCREEN_WIDTH], Position cameraPosition){
	for (int i = 0; i < Screen::SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < Screen::SCREEN_WIDTH; j++)
		{

			char tile = this->map[i][j + cameraPosition.x];
			buffer[i][j].Char.AsciiChar = tile;
			
			switch (tile)
			{
				case ' ' :
					buffer[i][j].Attributes = FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
					break;

				case 'w':
					buffer[i][j].Attributes = WHITE | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN;
					break;

				default:
					buffer[i][j].Attributes = WHITE;
					break;
			}
		}
	}
}
World::~World()
{

}
void World::changeCurrentMap(){
	if (this->currentMap == this->map){
		this->currentMap = this->map2;
	}
	else {
		this->currentMap = this->map;
	}
}

void World::update() {
}