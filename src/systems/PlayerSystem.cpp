#include "PlayerSystem.hpp"

PlayerSystem::PlayerSystem()
{
	_renderer->_tile = PLAYER;
	_renderer->_name = "Player";
	_input = std::make_unique<InputHandler<ActorSystem>>();
}

PlayerSystem::~PlayerSystem()
{
}

void PlayerSystem::update()
{
	_command = _input->update();
	if (_command != nullptr)
		_command->execute(*this);
}