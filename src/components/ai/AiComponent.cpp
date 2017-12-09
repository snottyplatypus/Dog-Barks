#include "AiComponent.hpp"

AiComponent::AiComponent()
{
	_state = std::make_unique<NoAi>();
}

AiComponent::~AiComponent()
{
}

void AiComponent::update(CommandedSystem & system)
{
	_state->update(system);
}
