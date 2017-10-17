#pragma once
#include <boost/multi_array.hpp>
#include <vector>
#include "Terrain.hpp"
#include "../systems/PlayerSystem.hpp"

class Level
{
public:
	Level(const int width = 32, const int height = 32);
	~Level();
	void update();

	std::shared_ptr<PlayerSystem> player_;
	std::vector<std::shared_ptr<ActorSystem>> actors_;

private:
	int width_;
	int height_;

public:
	boost::multi_array<Terrain, 2> terrain_;
};

extern Level level;