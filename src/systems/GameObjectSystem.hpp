#pragma once
#include <memory>
#include <string>
#include "../components/PositionComponent.hpp"
#include "../components/RenderComponent.hpp"
#include "../utils/Command.hpp"

struct GameObjectSystem 
{
	GameObjectSystem() {
		_pos = std::make_shared<PositionComponent>();
		_renderer = std::make_unique<RenderComponent>();
		_command = nullptr;
		_id = "object";
	}

	virtual ~GameObjectSystem() {}

	std::string _id;
	std::shared_ptr<PositionComponent> _pos;
	std::unique_ptr<RenderComponent> _renderer;
	std::shared_ptr<Command<GameObjectSystem>> _command;
};
