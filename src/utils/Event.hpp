#pragma once
#include "../components/PositionComponent.hpp"

enum Event
{
	NONE,
	MOVE,
};

struct MoveEvent
{
	int _id = NONE;
	int _x;
	int _y;
};