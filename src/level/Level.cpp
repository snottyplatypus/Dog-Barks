#include "Level.hpp"

Level::Level() : terrain_(boost::extents[width_][height_])
{
	player_ = std::make_shared<PlayerSystem>();
	actors_.push_back(player_);
}

Level::~Level()
{
}

void Level::update() 
{
	player_->update();
}
