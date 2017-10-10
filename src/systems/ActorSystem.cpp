#include "ActorSystem.hpp"

ActorSystem::ActorSystem() 
{
	pos_ = std::make_shared<PositionComponent>(1, 1);
	renderer_ = std::make_unique<RenderComponent>(pos_, '@');
	input_ = std::make_unique<InputHandler<ActorSystem>>();
	command_ = nullptr;
}

ActorSystem::~ActorSystem() 
{
}

void ActorSystem::update() 
{
	command_ = input_->update();
	if(command_ != nullptr)
		command_->execute(*this);
	renderer_->update(*pos_);
}