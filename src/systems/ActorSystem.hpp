#pragma once
#include "GameObjectSystem.hpp"
#include "../components/Command.hpp"

struct ActorSystem : public GameObjectSystem
{
	ActorSystem()
	{
		_renderer->_tile = ACTOR;
		_renderer->_name = "Actor";
		_command = nullptr;
	}

	virtual ~ActorSystem() {}
	virtual void update() = 0;

protected:
	std::shared_ptr<Command<ActorSystem>> _command;
};
