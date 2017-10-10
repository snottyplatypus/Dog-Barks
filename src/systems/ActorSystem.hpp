#pragma once
#include "../include/rltk.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/RenderComponent.hpp"
#include "../components/InputHandler.hpp"

struct ActorSystem
{
	ActorSystem() 
	{
		pos_ = std::make_shared<PositionComponent>(1, 1);
		renderer_ = std::make_unique<RenderComponent>('@');
		command_ = nullptr;
	}

	virtual ~ActorSystem() {}

	virtual void update() = 0;

	std::shared_ptr<PositionComponent> pos_;

protected:
	std::unique_ptr<RenderComponent> renderer_;
	std::shared_ptr<Command<ActorSystem>> command_;
};
