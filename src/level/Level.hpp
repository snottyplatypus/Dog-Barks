#pragma once
#include <boost/multi_array.hpp>
#include <vector>
#include <unordered_map>
#include "LevelTurnState.hpp"
#include "LevelRenderState.hpp"
#include "Terrain.hpp"
#include "../systems/ComMandedSystem.hpp"
#include "../systems/CameraSystem.hpp"
#include "../systems/LookingCursor.hpp"
#include "../systems/FireCursor.hpp"
#include "../ui/Effect.hpp"
#include "../ui/Gui.hpp"

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
	Level(const int width = 32, const int height = 32);
	~Level();
	void init();
	void update();
	void renderFov(CommandedSystem& system);
	void updateComputingMap(CommandedSystem& system);
	void generateLevel();
	void initTerrain();
	void generateRecursive(int x, int y, Room lastRoom);
	void fill(int x, int y, int width, int height, Terrain terrain);
	bool checkVisited(int x, int y, int width, int height);
	void setInBounds(int& x, int& y);

	std::unique_ptr<LevelTurnState> _turnState;
	std::unique_ptr<LevelRenderState> _renderState;
	Effect _effect;

	CameraSystem _camera;

	LookingCursor _lookingCursor;
	FireCursor _fireCursor;

	std::shared_ptr<CommandedSystem> _player;
	std::vector<std::shared_ptr<CommandedSystem>> _actors;

	int _width;
	int _height;

private:
	boost::multi_array<bool, 2> _generated;
	std::vector<Room> _rooms;

public:
	boost::multi_array<Terrain, 2> _terrain;
};

extern Level level;