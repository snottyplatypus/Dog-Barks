#pragma once
#include "../include/rltk.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/RenderComponent.hpp"
#include "../components/InputHandler.hpp"

struct ActorSystem
{
	ActorSystem();
	~ActorSystem();

	void update();

	std::shared_ptr<PositionComponent> pos_;

private:
	std::unique_ptr<RenderComponent> renderer_;
	std::unique_ptr<InputHandler<ActorSystem>> input_;
	std::shared_ptr<Command<ActorSystem>> command_;
};
