#pragma once
#include "ActorSystem.hpp"
#include "../components/InputHandler.hpp"

struct PlayerSystem : public ActorSystem
{
	PlayerSystem();
	~PlayerSystem();

	void update() override;

private:
	std::unique_ptr<InputHandler<ActorSystem>> input_;
};