#pragma once
#include "../components/PositionComponent.hpp"

enum Event
{
	NONE,
	MOVE,
	TRIGGER_LOOKING_CURSOR,
};

struct MoveEvent
{
	int _id = MOVE;
	int _x;
	int _y;
};