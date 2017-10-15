#include "Level.hpp"
#include <algorithm>
#include <iostream>

Level::Level(const int width, const int height) : width_(width), height_(height), terrain_(boost::extents[width_][height_])
{
	player_ = std::make_shared<PlayerSystem>();
	actors_.push_back(player_);

}

Level::~Level()
{
}

void Level::update() 
{
	for (int i = 0; i < width_; ++i)
		for (int j = 0; j < height_; ++j)
			terrain_[i][j].renderer_->update(i, j);
	for (auto i : actors_)
		i->update();
}
