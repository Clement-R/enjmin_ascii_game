#include "stdafx.h"
#include "Target.h"
#include <windows.h>
#include <string>

Target::Target(Position position)
{
	this->position = position;
}

Target::~Target()
{
}

void Target::update() {
	// Move target forward every 4 frames
	if (this->frameCounter % 4 == 0) {
		if (this->position.x - 1 > 0) {
			this->position.x -= this->speed;
		} else {
			this->toDestroy = true;
		}	
	}
	++this->frameCounter;
}

bool Target::needDestroy()
{
	return this->toDestroy;
}

void Target::setToDestroy()
{
	this->toDestroy = true;
}

