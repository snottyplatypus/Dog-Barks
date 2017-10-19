#pragma once
#include <memory>
#include "../components/RenderComponent.hpp"
#include "../Tile.hpp"

struct ActorSystem;

struct Terrain {

	Terrain(int tile = BLOCK3, std::string name = "Wall", bool isTransparent = false, bool isWalkable = false)
		: _isTransparent(isTransparent), _isWalkable(isWalkable), _actor(nullptr)
	{
		_renderer = std::make_shared<RenderComponent>(tile, name);
	}
	~Terrain() {}

	bool _isTransparent;
	bool _isWalkable;
	std::shared_ptr<ActorSystem> _actor;
	std::shared_ptr<RenderComponent> _renderer;
};