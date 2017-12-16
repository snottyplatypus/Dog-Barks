#pragma once
#include <libtcod/libtcod.hpp>
#include <memory>

struct ComputingMap
{
	ComputingMap() : _map(nullptr), _radius(10) {}

	~ComputingMap() {}

	void init(int width, int height)
	{
		_map = std::make_unique<TCODMap>(width, height);
		_path = std::make_unique<TCODPath>(_map.get());
	}

	std::unique_ptr<TCODMap> _map;
	std::unique_ptr<TCODPath> _path;
	int _radius;
};