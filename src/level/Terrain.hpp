#pragma once
#include <memory>
#include "../components/RenderComponent.hpp"
#include "../Tile.hpp"

struct ActorSystem;

struct Terrain {

	Terrain(int tile = NOTHING, std::string name = "Nothing", bool isTransparent = true, bool isWalkable = false, bool isWall = false)
		: _isTransparent(isTransparent), _isWalkable(isWalkable), _isWall(isWall), _actor(nullptr)
	{
		_renderer = std::make_shared<RenderComponent>(tile, name);
	}
	~Terrain() {}

	bool _isTransparent;
	bool _isWalkable;
	bool _isWall;
	std::shared_ptr<ActorSystem> _actor;
	std::shared_ptr<RenderComponent> _renderer;
};