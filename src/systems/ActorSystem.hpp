#pragma once
#include "../include/rltk.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/RenderComponent.hpp"

struct ActorSystem
{
	ActorSystem();
	~ActorSystem();

	void update();

	std::shared_ptr<PositionComponent> pos_;

private:
	std::unique_ptr<RenderComponent> renderer_;
};
