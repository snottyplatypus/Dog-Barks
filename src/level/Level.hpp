#pragma once
#include <boost/multi_array.hpp>
#include <vector>
#include "Terrain.hpp"
#include "../systems/PlayerSystem.hpp"

enum GenerationType {
	CLASSIC,
};

class Level
{
public:
	Level(const int width = 48, const int height = 48);
	~Level();
	void update();
	void generateLevel(int type);
	void generateClassic(int x, int y);
	void fill(int x, int y, int width, int height, Terrain terrain);
	bool checkVisited(int x, int y, int width, int height);
	void setIntBounds(int& x, int& y);

	std::shared_ptr<PlayerSystem> _player;
	std::vector<std::shared_ptr<ActorSystem>> _actors;

private:
	int _width;
	int _height;

public:
	boost::multi_array<Terrain, 2> _terrain;
	boost::multi_array<bool, 2> _visited;
};

extern Level level;