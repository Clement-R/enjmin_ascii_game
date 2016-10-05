#pragma once
#include "Entity.h"

class World : public Entity
{
public:

	int gravity = 1;

	void update();
	World();
	~World();
};

