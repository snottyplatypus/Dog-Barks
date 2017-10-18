#pragma once
#include "ActorSystem.hpp"
#include "../components/InputHandler.hpp"

struct PlayerSystem : public ActorSystem
{
	PlayerSystem(int x = 1, int y = 1);
	~PlayerSystem();

	void update() override;

private:
	std::unique_ptr<InputHandler<ActorSystem>> _input;
};