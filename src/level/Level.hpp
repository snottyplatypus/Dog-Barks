#pragma once
#include <boost/multi_array.hpp>
#include <vector>
#include <unordered_map>
#include "Terrain.hpp"
#include "../systems/PlayerSystem.hpp"

struct Room {
	int _x;
	int _y;
	int _width = 0;
	int _height = 0;
	int _doors = 0;
};

class Level
{
public:
	Level(const int width = 24, const int height = 24);
	~Level();
	void update();
	void generateLevel();
	void initTerrain();
	void generateRecursive(int x, int y, Room lastRoom);
	void fill(int x, int y, int width, int height, Terrain terrain);
	bool checkVisited(int x, int y, int width, int height);
	void setInBounds(int& x, int& y);

	std::shared_ptr<PlayerSystem> _player;
	std::vector<std::shared_ptr<ActorSystem>> _actors;

	int _width;
	int _height;

private:
	boost::multi_array<bool, 2> _generated;
	std::vector<Room> _rooms;

public:
	boost::multi_array<Terrain, 2> _terrain;
};

extern Level level;