#pragma once
#include "../components/PositionComponent.hpp"

enum Event
{
	NONE,
	CANCEL,
	MOVE,
	TRIGGER_LOOKING_CURSOR,
	TRIGGER_FIRE_CURSOR,
	LOOKING_TERRAIN,
	LOOKING_ACTOR,
};

struct MoveEvent
{
	int _id = MOVE;
	int _x;
	int _y;
};

struct LookingEvent
{
	int _id;
	int _x;
	int _y;
};