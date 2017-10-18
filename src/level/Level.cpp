#include "Level.hpp"
#include "../include/libtcod/libtcod.hpp"
#include "../utils/Global.hpp"
#include <algorithm>
#include <iostream>

Level::Level(const int width, const int height) 
	: _width(width), _height(height), _terrain(boost::extents[_width][_height]), _visited(boost::extents[_width][_height])
{
	_player = std::make_shared<PlayerSystem>();
	_actors.push_back(_player);

	std::fill(_visited.origin(), _visited.origin() + _visited.size(), false);
	std::cout << _visited[0][0];
	generateLevel(CLASSIC);
}

Level::~Level()
{
}

void Level::update() 
{
	for (auto i : _actors) {
		i->update();
		_terrain[i->_pos->_x][i->_pos->_y]._actor = i;
	}
	for (int i = 0; i < _width; ++i) {
		for (int j = 0; j < _height; ++j) {
			if (_terrain[i][j]._actor == nullptr)
				_terrain[i][j]._renderer->update(i, j);
			else
				_terrain[i][j]._actor->_renderer->update(i, j);
		}
	}
}

void Level::generateLevel(int type)
{
	if (type == CLASSIC)
		generateClassic(1, 1);
}

void Level::generateClassic(int x, int y)
{
	setIntBounds(x, y);
	int width = rng.getInt(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
	int height = rng.getInt(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
	int x2 = x + width;
	int y2 = y + height;
	setIntBounds(x2, y2);

	if (x < _width - MIN_ROOM_SIZE && y < _height - MIN_ROOM_SIZE) {
		if (!checkVisited(x, y, x2 - x, y2 - y)) {
			fill(x, y, x2 - x, y2 - y, { '.', "Ground", true, true });

			for (int i = x; i < x2; i++)
				for (int j = y; j < y2; j++)
					_visited[i][j] = true;

			generateClassic(x2 + 1, y + rng.getInt(0, 5, -1));
			generateClassic(x + rng.getInt(0, 5, -1), y2 + 1);
		}
	}
}

void Level::fill(int x, int y, int width, int height, Terrain terrain)
{
	
	for (int i = x; i < x + width; ++i)
		for (int j = y; j < y + height; ++j)
			_terrain[i][j] = terrain;
}

bool Level::checkVisited(int x, int y, int width, int height)
{
	for (int i = x; i < x + width; i++)
		for (int j = y; j < y + height; j++)
			if (_visited[i][j])
				return true;
	return false;
}

void Level::setIntBounds(int& x, int& y)
{
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > _width)
		x = _width - 1;
	if (y > _height)
		y = _height - 1;
}
