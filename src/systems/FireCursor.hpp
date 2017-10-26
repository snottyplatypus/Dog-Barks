#pragma once
#include "CommandedSystem.hpp"
#include "../utils/Tile.hpp"
#include "../utils/EventManager.hpp"

struct FireCursor : public CommandedSystem
{
	FireCursor(int x = 1, int y = 1)
	{
		_renderer->_tile = CURSOR;
		_id = "cursor";
		_renderer->_bg = TCODColor::desaturatedYellow * 1.5f;
	}
	~FireCursor() {}
	void update()
	{
		if (_command != nullptr)
			_command->execute(*this);
		eventManager.onNotify({ LOOKING_ACTOR, _pos->_x, _pos->_y });
	}
};