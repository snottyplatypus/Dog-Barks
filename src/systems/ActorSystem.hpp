#pragma once
#include "../include/rltk.hpp"
#include "GameObjectSystem.hpp"
#include "../components/Command.hpp"

struct ActorSystem : public GameObjectSystem
{
	ActorSystem() 
	{
		renderer_->tile_ = '@';
		command_ = nullptr;
	}

	virtual ~ActorSystem() {}

	virtual void update() override = 0;

protected:
	std::shared_ptr<Command<ActorSystem>> command_;
};
