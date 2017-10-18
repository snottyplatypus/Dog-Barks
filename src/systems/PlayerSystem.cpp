#include "PlayerSystem.hpp"

PlayerSystem::PlayerSystem(int x, int y)
{
	_renderer->_tile = PLAYER;
	_renderer->_name = "Player";
	_input = std::make_unique<InputHandler<ActorSystem>>();
	_pos->_x = x;
	_pos->_y = y;
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