#pragma once
#include "../components/PositionComponent.hpp"

enum Event
{
	NONE,
	MOVE,
	TRIGGER_LOOKING_CURSOR,
	LOOKING,
};

struct MoveEvent
{
	int _id = MOVE;
	int _x;
	int _y;
};

struct LookingEvent
{
	int _id = LOOKING;
	int _x;
	int _y;
};