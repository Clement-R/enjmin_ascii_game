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
	ifstream is("map");
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
			}
			counter++;
		}
	}
}

void World::draw(CHAR_INFO(&buffer)[Screen::SCREEN_HEIGHT][Screen::SCREEN_WIDTH], Position cameraPosition){
	for (int i = 0; i < Screen::SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < Screen::SCREEN_WIDTH; j++)
		{
			buffer[i][j].Char.AsciiChar = this->map[i][j + cameraPosition.x];
			buffer[i][j].Attributes = WHITE;
		}
	}
}
World::~World()
{

}

void World::update() {
}