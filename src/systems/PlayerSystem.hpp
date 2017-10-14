#pragma once
#include "ActorSystem.hpp"
#include "../components/InputHandler.hpp"

struct PlayerSystem : public ActorSystem
{
	PlayerSystem()
	{
		renderer_->tile_ = PLAYER;
		renderer_->name_ = "Player";
		input_ = std::make_unique<InputHandler<ActorSystem>>();
	}

	~PlayerSystem() {}

	void update() override
	{
		command_ = input_->update();
		if (command_ != nullptr)
			command_->execute(*this);
		renderer_->update(*pos_);
	}

private:
	std::unique_ptr<InputHandler<ActorSystem>> input_;
};