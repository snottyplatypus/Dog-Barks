#pragma once
#include "../include/libtcod/libtcod.hpp"
#include <memory>

struct ComputingMap
{
	ComputingMap() : _map(nullptr), _radius(10) {}

	~ComputingMap() {}

	void init(int width, int height)
	{
		_map = std::make_unique<TCODMap>(width, height);
	}

	std::unique_ptr<TCODMap> _map;
	int _radius;
};