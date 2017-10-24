#include "Level.hpp"
#include "../include/libtcod/libtcod.hpp"
#include "../utils/Global.hpp"
#include "../Tile.hpp"
#include <algorithm>
#include <iostream>

Level::Level(const int width, const int height) 
	: _width(width), _height(height), _terrain(boost::extents[_width][_height]),
	  _generated(boost::extents[_width][_height])
{
	_player = std::make_shared<PlayerSystem>(2, 2);
	_actors.push_back(_player);

	std::fill(_generated.origin(), _generated.origin() + _generated.size(), false);
	generateLevel();
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
				_terrain[i][j]._renderer->update({ i, j });
			else
				_terrain[i][j]._actor->_renderer->update({ i, j });
		}
	}
}

void Level::generateLevel()
{
	initTerrain();
	generateRecursive(_width / 2 - (MAX_ROOM_SIZE - 2) / 2, _height / 2 - (MAX_ROOM_SIZE - 2) / 2, { 0, 0 });

	std::sort(_rooms.begin(), _rooms.end(), [](const Room& a, const Room& b) -> bool { return a._x < b._x; });
	std::sort(_rooms.begin(), _rooms.end(), [](const Room& a, const Room& b) -> bool { return a._y < b._y; });

	_player->_pos->_x = _rooms[0]._x + 1;
	_player->_pos->_y = _rooms[0]._y - 1;
	
	for (auto i : _rooms)  {
		for (auto j : _rooms)  {
			if (j._x != i._x || j._y != i._y) {
				if (j._x == i._x) {

					int x = 0;
					if(j._width <= i._width)
						x = i._x + rng.getInt(1, j._width - 2);
					else
						x = i._x + rng.getInt(1, i._width - 2);
					if (i._doors < 3) {
						i._doors++;
						_terrain[x][i._y] = { DOOR, "Door", false, true, false, TCODColor::sepia, TCODColor::darkestSepia * 0.5f };
					}
				}
				if (j._y == i._y) {

					int y = 0;
					if (j._height <= i._height)
						y = i._y + rng.getInt(1, j._height - 2);
					else
						y = i._y + rng.getInt(1, i._height - 2);
					if (i._doors < 3) {
						i._doors++;
						_terrain[i._x][y] = { DOOR, "Door", false, true, false, TCODColor::sepia, TCODColor::darkestSepia * 0.5f };
					}
				}
			}
		}
	}
}

void Level::initTerrain()
{
	fill(0, 0, _width, _height, { BLOCK1, "Ground", true, false, false, TCODColor::grey });
	for (int i = 1; i < _width - 1; ++i)
		for (int j = 1; j < _height - 1; ++j)
			switch (rng.getInt(0, 3)) {
			case 0:
				_terrain[i][j] = { '.', "Ground", true, true, false, TCODColor::chartreuse, {0, 13, 0 } }; break;
			case 1:
				_terrain[i][j] = { ',', "Ground", true, true, false, TCODColor::chartreuse,{ 0, 13, 0 } }; break;
			case 2:
				_terrain[i][j] = { ';', "Ground", true, true, false, TCODColor::chartreuse,{ 0, 13, 0 } }; break;
			case 3:
				_terrain[i][j] = { '"', "Ground", true, true, false, TCODColor::chartreuse,{ 0, 13, 0 } }; break;
			} 
}

void Level::generateRecursive(int x, int y, Room lastRoom)
{
	int width = rng.getInt(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
	int height = rng.getInt(MIN_ROOM_SIZE, MAX_ROOM_SIZE);

	if (x == lastRoom._x + 1)
		x = x - width;
	if (y == lastRoom._y + 1)
		y = y - height;

	int x2 = x + width;
	int y2 = y + height;
	setInBounds(x, y);
	setInBounds(x2, y2);
	width = x2 - x;
	height = y2 - y;

	if (x < _width - MAX_ROOM_SIZE && y < _height - MAX_ROOM_SIZE && x > 0 && y > 0) {
		if (!checkVisited(x, y, width, height)) {

			fill(x, y, width, height, { BLOCK3, "Wall", false, false, true, TCODColor::lightestSepia });
			fill(x + 1, y + 1, width - 2, height - 2, { FLOOR, "Ground", true, true, false, TCODColor::lightSepia, TCODColor::darkestSepia * 0.5f });

			for (int i = x + 1; i < x2 - 1; i++)
				for (int j = y + 1; j < y2 - 1; j++)
					_generated[i][j] = true;

			_rooms.push_back({ x, y, width, height });

			generateRecursive(x2 - 1, y, { x, y, width, height });
			generateRecursive(x, y2 - 1, { x, y, width, height });
			generateRecursive(x + 1, y, { x, y, width, height });
			generateRecursive(x, y + 1, { x, y, width, height });
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
			if (_generated[i][j])
				return true;
	return false;
}

void Level::setInBounds(int& x, int& y)
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
