#pragma once
struct Position
{
public:
	Position(const int x = 0, const int y = 0) : x_(x), y_(y) {}
	~Position() {}

	int x_;
	int y_;
};