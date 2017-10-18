#include "Level.hpp"
#include <algorithm>
#include <iostream>

Level::Level(const int width, const int height) : _width(width), _height(height), _terrain(boost::extents[_width][_height])
{
	player_ = std::make_shared<PlayerSystem>();
	actors_.push_back(player_);

}

Level::~Level()
{
}

void Level::update() 
{
	for (auto i : actors_) {
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
