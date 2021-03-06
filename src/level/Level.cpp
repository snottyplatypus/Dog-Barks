#include "Level.hpp"
#include <libtcod/libtcod.hpp>
#include "../utils/Global.hpp"
#include "../utils/InputHandler.hpp"
#include "../components/ai/AiState.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>

Level::Level(const int width, const int height) 
	: _width(width), _height(height), _terrain(boost::extents[_width][_height]),
	  _generated(boost::extents[_width][_height]), _player(nullptr)
{
	_gameState = std::make_unique<GenerateState>();
	_turnState = std::make_unique<PlayerTurn>();
	_renderState = std::make_unique<RenderBase>();
}

Level::~Level()
{
}

void Level::init()
{
	_gameState->enter(*this);
}

void Level::update()
{
	_gameState->update(*this);
}

void Level::renderFov(CommandedSystem& system)
{
	for (int i = 0; i < _width; i++) {
		for (int j = 0; j < _height; j++) {
			if (system._computing->_map->isInFov(i, j)) {
				if (_terrain[i][j]._actor == nullptr)
					_terrain[i][j]._renderer->update({ i + _camera._pos->_x, j + _camera._pos->_y });
				else
					_terrain[i][j]._actor->_renderer->update({ i + _camera._pos->_x, j + _camera._pos->_y });
			}
			else
				_terrain[i][j]._renderer->update({ i + _camera._pos->_x, j + _camera._pos->_y }, 0.1f);
		}
	}
}

void Level::renderAll()
{
	for (int i = 0; i < _width; i++) {
		for (int j = 0; j < _height; j++) {
		if (_terrain[i][j]._actor == nullptr)
			_terrain[i][j]._renderer->update({ i + _camera._pos->_x, j + _camera._pos->_y });
		else
			_terrain[i][j]._actor->_renderer->update({ i + _camera._pos->_x, j + _camera._pos->_y });
		}
	}
}

void Level::updateComputingMap(CommandedSystem& system)
{
	for (int i(0); i < _width; i++)
		for (int j(0); j < _height; j++)
			system._computing->_map->setProperties(i, j, _terrain[i][j]._isTransparent, _terrain[i][j]._isWalkable);
}

void Level::generateLevel()
{
	std::fill(_generated.origin(), _generated.origin() + _generated.size(), false);
	initTerrain();
	generateRecursive(_width / 2 - (config.MAX_ROOM_SIZE - 2) / 2, _height / 2 - (config.MAX_ROOM_SIZE - 2) / 2, { 0, 0 });

	std::sort(_rooms.begin(), _rooms.end(), [](const Room& a, const Room& b) -> bool { return a._x < b._x; });
	std::sort(_rooms.begin(), _rooms.end(), [](const Room& a, const Room& b) -> bool { return a._y < b._y; });

	_player->_pos->_x = _rooms[0]._x + 1;
	_player->_pos->_y = _rooms[0]._y - config.DISTANCE_BORDERS / 2;
	
	for (auto i : _rooms) {
		for (auto j : _rooms) {
			if (j._x != i._x || j._y != i._y) {
				if (j._x == i._x) {

					int x = 0;
					if (j._width <= i._width)
						x = i._x + rng.getInt(1, j._width - 2);
					else
						x = i._x + rng.getInt(1, i._width - 2);
					if (i._doors < 3) {
						i._doors++;
						_terrain[x][i._y] = { "door", "door", false, true, TCODColor::lightSepia, TCODColor::darkestSepia * 0.5f };
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
						_terrain[i._x][y] = { "door", "door", false, true, TCODColor::lightSepia, TCODColor::darkestSepia * 0.5f };
					}
				}
			}
		}
	}
	
	for (auto i : _rooms) {
		int nActor = rng.getInt(0, config.MAX_ENEMY_PER_ROOM);
		for (int j = 0; j < nActor; j++) {
			_actors.push_back(std::make_shared<CommandedSystem>(i._x + rng.getInt(1, i._width - 2), i._y + rng.getInt(1, i._height - 2)));
			_actors.back()->_renderer->_tile = "gang_b";
			_actors.back()->init(_width, _height);
			_actors.back()->_ai->_state->transit<WanderingState>(*_actors.back());
			_actors.back()->_faction = data._factions["gang_b"];
			int index = rng.getInt(1, static_cast<int>(data._wKeys.size()) - 1);
			_actors.back()->_inventory->_held = data._weapons[data._wKeys[index]];
		}
	}
}

void Level::initTerrain()
{
	for (int i = 0; i < _width; ++i)
		for (int j = 0; j < _height; ++j)
			_terrain[i][j]._void = true;
	fill(1, 1, _width - 2, _height - 2, { "block1", "escape", true, true, TCODColor::desaturatedGreen, TCODColor::black, true });
	for (int i = 2; i < _width - 2; ++i)
		for (int j = 2; j < _height - 2; ++j)
			switch (rng.getInt(0, 3)) {
			case 0:
				_terrain[i][j] = { "ground", "grass", true, true, TCODColor::chartreuse, {0, 13, 0 } }; break;
			case 1:
				_terrain[i][j] = { "grass1", "grass", true, true, TCODColor::chartreuse,{ 0, 13, 0 } }; break;
			case 2:
				_terrain[i][j] = { "grass2", "grass", true, true, TCODColor::chartreuse,{ 0, 13, 0 } }; break;
			case 3:
				_terrain[i][j] = { "grass3", "grass", true, true, TCODColor::chartreuse,{ 0, 13, 0 } }; break;
			} 
}

void Level::generateRecursive(int x, int y, Room lastRoom)
{
	int width = rng.getInt(config.MIN_ROOM_SIZE, config.MAX_ROOM_SIZE);
	int height = rng.getInt(config.MIN_ROOM_SIZE, config.MAX_ROOM_SIZE);

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

	int dist = config.DISTANCE_BORDERS - 1;

	if (x < _width - config.MAX_ROOM_SIZE - dist && y < _height - config.MAX_ROOM_SIZE - dist && x > dist && y > dist) {
		if (!checkVisited(x, y, width, height)) {

			fill(x, y, width, height, { "block3", "wall", false, false, TCODColor::lightestSepia, TCODColor::darkestSepia * 0.5f });
			fill(x + 1, y + 1, width - 2, height - 2, { "floor", "floor", true, true, TCODColor::lightSepia, TCODColor::darkestSepia * 0.5f });

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
	x = std::max(x, config.DISTANCE_BORDERS - 1);
	y = std::max(y, config.DISTANCE_BORDERS - 1);
	x = std::min(x, _width + config.DISTANCE_BORDERS - 1);
	y = std::min(y, _height + config.DISTANCE_BORDERS - 1);
}
