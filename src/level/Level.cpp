#include "Level.hpp"

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
	for (auto i : actors_)
		i->update();
}
