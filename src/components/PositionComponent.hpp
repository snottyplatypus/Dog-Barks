#pragma once
struct PositionComponent
{
	PositionComponent(const int x = 0, const int y = 0) : _x(x), _y(y) {}
	~PositionComponent() {}

	int _x;
	int _y;
};