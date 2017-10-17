#pragma once
#include <memory>
#include "../components/RenderComponent.hpp"

struct ActorSystem;

struct Terrain {

	Terrain(): isTransparent_(true), isWalkable_(true), actor_(nullptr)
	{
		renderer_ = std::make_shared<RenderComponent>('.', "Ground");
	}
	~Terrain() {}

	bool isTransparent_;
	bool isWalkable_;
	std::shared_ptr<ActorSystem> actor_;
	std::shared_ptr<RenderComponent> renderer_;
};