#pragma once
#include <memory>
#include "../components/RenderComponent.hpp"

struct ActorSystem;

struct Terrain {

	Terrain(): _isTransparent(true), _isWalkable(true), _actor(nullptr)
	{
		_renderer = std::make_shared<RenderComponent>('.', "Ground");
	}
	~Terrain() {}

	bool _isTransparent;
	bool _isWalkable;
	std::shared_ptr<ActorSystem> _actor;
	std::shared_ptr<RenderComponent> _renderer;
};