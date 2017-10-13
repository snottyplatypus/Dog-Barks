#include "Level.hpp"

Level::Level() : terrain_(boost::extents[width_][height_])
{
	player_ = std::make_shared<PlayerSystem>();
}

Level::~Level()
{
}

void Level::update() 
{
	player_->update();
}
