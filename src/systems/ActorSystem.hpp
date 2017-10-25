#pragma once
#include "GameObjectSystem.hpp"

struct ActorSystem : public GameObjectSystem
{
	ActorSystem(int x, int y, int tile = ACTOR, std::string name = "Actor")
	{
		_pos->_x = x;
		_pos->_y = y;
		_renderer->_tile = tile;
		_renderer->_name = name;
	}

	~ActorSystem() {}
	void update() 
	{
		if (_command != nullptr)
			_command->execute(*this);
	}
};
