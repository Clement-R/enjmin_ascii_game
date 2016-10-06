#include "stdafx.h"
#include "Target.h"

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
		++this->position.x;
	}
	this->frameCounter++;
}