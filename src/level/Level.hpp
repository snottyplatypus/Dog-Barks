#pragma once
#include <boost\multi_array.hpp>
#include "Terrain.hpp"
#include "../systems/PlayerSystem.hpp"

class Level
{
public:
	Level();
	~Level();
	void update();

	boost::multi_array<Terrain, 2> terrain_;
	std::shared_ptr<PlayerSystem> player_;

private:
	int width_ = 64;
	int height_ = 64;
};

