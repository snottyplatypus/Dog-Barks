#include "Level.hpp"
#include "../include/libtcod/libtcod.hpp"
#include "../utils/Global.hpp"
#include "../utils/InputHandler.hpp"
#include "../utils/Tile.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>

Level::Level(const int width, const int height) 
	: _gameState(PLAYER_TURN), _width(width), _height(height), _terrain(boost::extents[_width][_height]),
	  _generated(boost::extents[_width][_height]), _time(0.0f)
{
	_player = std::make_shared<CommandedSystem>(2, 2, PLAYER, "You");
	_actors.push_back(_player);

	_camera.lockOn({ SCREEN_WIDTH / 2 - _width / 2, SCREEN_HEIGHT / 2 - _height / 2 });

	generateLevel();
}

Level::~Level()
{
}

void Level::update()
{

	_time += TCODSystem::getLastFrameLength();

	switch (_gameState) {
	case PLAYER_TURN:
		inputHandler.onObject(*_player);
		_player->update();
		break;
	case CURSOR_MODE_L:
		inputHandler.onObject(_lookingCursor);
		_lookingCursor.update();
		break;
	case CURSOR_MODE_F:
		inputHandler.onObject(_fireCursor);
		_fireCursor.update();
		break;
	}

	for (auto i : _actors) {
		_terrain[i->_pos->_x][i->_pos->_y]._actor = i;
		i->_renderer->_bg = _terrain[i->_pos->_x][i->_pos->_y]._renderer->_bg;
	}
	for (int i = 0; i < _width; ++i) {
		for (int j = 0; j < _height; ++j) {
			if (_terrain[i][j]._actor == nullptr)
				_terrain[i][j]._renderer->update({ i + _camera._pos->_x, j + _camera._pos->_y });
			else
				_terrain[i][j]._actor->_renderer->update({ i + _camera._pos->_x, j + _camera._pos->_y });
		}
	}
	if (_gameState == CURSOR_MODE_L) {
		_lookingCursor._renderer->_bg = _terrain[_lookingCursor._pos->_x][_lookingCursor._pos->_y]._renderer->_bg;
		if (std::fmodf(_time, 1.0f) >= 0.5f)
			_lookingCursor._renderer->update({ _lookingCursor._pos->_x + _camera._pos->_x, _lookingCursor._pos->_y + _camera._pos->_y });
	}
	if (_gameState == CURSOR_MODE_F)
		_fireCursor.render(*_player->_pos, *_camera._pos, _time);
}

void Level::generateLevel()
{
	std::fill(_generated.origin(), _generated.origin() + _generated.size(), false);
	initTerrain();
	generateRecursive(_width / 2 - (MAX_ROOM_SIZE - 2) / 2, _height / 2 - (MAX_ROOM_SIZE - 2) / 2, { 0, 0 });

	std::sort(_rooms.begin(), _rooms.end(), [](const Room& a, const Room& b) -> bool { return a._x < b._x; });
	std::sort(_rooms.begin(), _rooms.end(), [](const Room& a, const Room& b) -> bool { return a._y < b._y; });

	_player->_pos->_x = _rooms[0]._x + 1;
	_player->_pos->_y = _rooms[0]._y - DISTANCE_BORDERS / 2;
	
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
						_terrain[x][i._y] = { DOOR, "Door", false, true, TCODColor::lightSepia, TCODColor::darkestSepia * 0.5f };
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
						_terrain[i._x][y] = { DOOR, "Door", false, true, TCODColor::lightSepia, TCODColor::darkestSepia * 0.5f };
					}
				}
			}
		}
	}
}

void Level::initTerrain()
{
	for (int i = 0; i < _width; ++i)
		for (int j = 0; j < _height; ++j)
			_terrain[i][j]._void = true;
	fill(1, 1, _width - 2, _height - 2, { BLOCK1, "Escape", true, true, TCODColor::desaturatedGreen, TCODColor::black, true });
	for (int i = 2; i < _width - 2; ++i)
		for (int j = 2; j < _height - 2; ++j)
			switch (rng.getInt(0, 3)) {
			case 0:
				_terrain[i][j] = { '.', "Ground", true, true, TCODColor::chartreuse, {0, 13, 0 } }; break;
			case 1:
				_terrain[i][j] = { ',', "Ground", true, true, TCODColor::chartreuse,{ 0, 13, 0 } }; break;
			case 2:
				_terrain[i][j] = { ';', "Ground", true, true, TCODColor::chartreuse,{ 0, 13, 0 } }; break;
			case 3:
				_terrain[i][j] = { '"', "Ground", true, true, TCODColor::chartreuse,{ 0, 13, 0 } }; break;
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

	int dist = DISTANCE_BORDERS - 1;

	if (x < _width - MAX_ROOM_SIZE - dist && y < _height - MAX_ROOM_SIZE - dist && x > dist && y > dist) {
		if (!checkVisited(x, y, width, height)) {

			fill(x, y, width, height, { BLOCK3, "Wall", false, false, TCODColor::lightestSepia });
			fill(x + 1, y + 1, width - 2, height - 2, { FLOOR, "Floor", true, true, TCODColor::lightSepia, TCODColor::darkestSepia * 0.5f });

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
	if (x < DISTANCE_BORDERS - 1)
		x = DISTANCE_BORDERS - 1;
	if (y < DISTANCE_BORDERS - 1)
		y = DISTANCE_BORDERS - 1;
	if (x > _width + DISTANCE_BORDERS - 1)
		x = _width - DISTANCE_BORDERS;
	if (y > _height + DISTANCE_BORDERS - 1)
		y = _height - DISTANCE_BORDERS;
}
