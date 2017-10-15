#pragma once
#include "GameObjectSystem.hpp"
#include "../components/Command.hpp"

struct ActorSystem : public GameObjectSystem
{
	ActorSystem()
	{
		renderer_->tile_ = ACTOR;
		renderer_->name_ = "Actor";
		command_ = nullptr;
	}

	virtual ~ActorSystem() {}
	virtual void update() = 0;

protected:
	std::shared_ptr<Command<ActorSystem>> command_;
};
