#pragma once
struct PositionComponent
{
	int _x = 0;
	int _y = 0;

	PositionComponent operator+(PositionComponent const& b) { return { _x + b._x, _y + b._y }; }
	bool operator==(PositionComponent const& b) { return _x == b._x && _y == b._y; }
	bool operator!=(PositionComponent const& b) { return _x != b._x || _y != b._y; }
};