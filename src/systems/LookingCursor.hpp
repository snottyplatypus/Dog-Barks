#pragma once
#include "CommandedSystem.hpp"
#include "../utils/Tile.hpp"

struct LookingCursor : public CommandedSystem
{
	LookingCursor(int x = 1, int y = 1) 
	{
		_renderer->_tile = CURSOR;
		_id = "cursor";
	}
	~LookingCursor() {}
	void update()
	{
		if (_command != nullptr)
			_command->execute(*this);
	}
};