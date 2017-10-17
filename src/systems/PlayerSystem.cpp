#include "PlayerSystem.hpp"

PlayerSystem::PlayerSystem()
{
	renderer_->tile_ = PLAYER;
	renderer_->name_ = "Player";
	input_ = std::make_unique<InputHandler<ActorSystem>>();
}

PlayerSystem::~PlayerSystem()
{
}

void PlayerSystem::update()
{
	command_ = input_->update();
	if (command_ != nullptr)
		command_->execute(*this);
}