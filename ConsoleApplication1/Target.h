#pragma once
#include "Entity.h"
#include "Position.h"

class Target : public Entity
{
	public:
		Target(Position position);
		~Target();

		void update();
		bool needDestroy();

	private:
		int frameCounter = 0;
		bool toDestroy = false;
};

