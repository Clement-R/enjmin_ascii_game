#pragma once

#include "Position.h"

class Entity
{
	public:
		Position position;
		virtual void update() = 0;
};
