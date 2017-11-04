#pragma once
#include "CommandedSystem.hpp"
#include "../level/Tile.hpp"
#include "../utils/EventManager.hpp"

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
		if (_move != nullptr)
			_move->execute(*this);
		if (_interaction != nullptr) {
			_interaction->execute(*this);
			_interaction = nullptr;
		}
		eventManager.onLook({ LOOKING_TERRAIN, _pos->_x, _pos->_y });
	}
};