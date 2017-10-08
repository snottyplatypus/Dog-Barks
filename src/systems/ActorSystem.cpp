#include "ActorSystem.hpp"

ActorSystem::ActorSystem() 
{
	pos_ = std::make_shared<PositionComponent>(1, 1);
	renderer_ = std::make_unique<RenderComponent>(pos_, '@');
}

ActorSystem::~ActorSystem() 
{
}

void ActorSystem::update() 
{
	renderer_->update();
}