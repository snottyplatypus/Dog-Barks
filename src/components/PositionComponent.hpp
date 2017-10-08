#pragma once
struct PositionComponent
{
public:
	PositionComponent(const int x = 0, const int y = 0) : x_(x), y_(y) {}
	~PositionComponent() {}

	int x_;
	int y_;
};