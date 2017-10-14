#pragma once
#include <memory>
#include <string>
#include "../components/PositionComponent.hpp"
#include "../components/RenderComponent.hpp"

struct GameObjectSystem {
	GameObjectSystem() {
		pos_ = std::make_shared<PositionComponent>();
		renderer_ = std::make_unique<RenderComponent>();
	}
	virtual ~GameObjectSystem() {}

	virtual void update() = 0;

	std::shared_ptr<PositionComponent> pos_;
	std::unique_ptr<RenderComponent> renderer_;
};