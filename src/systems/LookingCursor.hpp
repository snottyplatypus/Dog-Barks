#pragma once
#include "CommandedSystem.hpp"
#include "../utils/EventManager.hpp"

struct LookingCursor : public CommandedSystem
{
	LookingCursor(int x = 1, int y = 1) 
	{
		_renderer->_tile = "cursor";
		_id = "cursor";
		_inventory = nullptr;
		_body = nullptr;
		_computing = nullptr;
		_ai = std::make_shared<AiComponent>();
	}

	~LookingCursor() {}

	void update(CommandedSystem& origin)
	{
		if (_move != nullptr)
			_move->execute(*this);
		if (_interaction != nullptr) {
			_interaction->execute(*this);
			_interaction = nullptr;
		}
		eventManager.onNotify(std::make_unique<LookingEvent>(_pos->_x, _pos->_y), origin);
	}
};