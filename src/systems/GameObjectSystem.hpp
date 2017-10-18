#pragma once
#include <memory>
#include "../components/PositionComponent.hpp"
#include "../components/RenderComponent.hpp"

struct GameObjectSystem 
{
	GameObjectSystem() {
		_pos = std::make_shared<PositionComponent>();
		_renderer = std::make_unique<RenderComponent>();
	}

	virtual ~GameObjectSystem() {}

	std::shared_ptr<PositionComponent> _pos;
	std::unique_ptr<RenderComponent> _renderer;
};
