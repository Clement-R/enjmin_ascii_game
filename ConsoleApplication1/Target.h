#pragma once
#include "Entity.h"
#include "Position.h"

class Target : public Entity
{
	public:
		static const int TARGET_WIDTH = 2;
		static const int TARGET_HEIGHT = 4;

		int speed = 2;

		Target(Position position);
		~Target();

		void update();
		bool needDestroy();
		void setToDestroy();

	private:
		int frameCounter = 0;
		bool toDestroy = false;
};

