#pragma once
#include "GameObjectSystem.hpp"

struct CommandedSystem : public GameObjectSystem
{
	CommandedSystem(int x = 1, int y = 1, int tile = ACTOR, std::string name = "Actor")
	{
		_pos->_x = x;
		_pos->_y = y;
		_renderer->_tile = tile;
		_renderer->_name = name;
		_id = "actor";
	}

	~CommandedSystem() {}
	void update() 
	{
		if (_command != nullptr)
			_command->execute(*this);
	}
};
