#pragma once
#include "CommandedSystem.hpp"
#include "CameraSystem.hpp"
#include "../utils/Global.hpp"
#include "../utils/EventManager.hpp"
#include "../utils/Line.hpp"
#include "../utils/Geometry.hpp"
#include <iostream>

struct FireCursor : public CommandedSystem
{
	FireCursor(int x = 1, int y = 1)
	{
		_fireLine._bg = TCODColor::desaturatedYellow;
		_renderer->_tile = "cursor";
		_id = "cursor";
		_renderer->_bg = TCODColor::desaturatedYellow;
		_inventory = nullptr;
		_body = nullptr;
		_computing = nullptr;
	}

	~FireCursor() {}

	void update(CommandedSystem& origin)
	{
		if (_move != nullptr)
			_move->execute(*this);
		if (_interaction != nullptr) {
			_interaction->execute(origin);
			_interaction = nullptr;
		}
		eventManager.onLook({ AIMING, _pos->_x, _pos->_y, *origin._pos });
	}

	void render(PositionComponent& origin, PositionComponent& mod)
	{
		PositionComponent aux = { db::vec_2p(origin, *_pos) };
		PositionComponent off;
		if(aux._x != 0 && aux._x > 0)
			off._x = aux._x / aux._x;
		else if (aux._x != 0 && aux._x < 0)
			off._x = -1;
		if (aux._y != 0 && aux._y > 0)
			off._y = aux._y / aux._y;
		else if (aux._y != 0 && aux._y < 0)
			off._y = -1;
		_lastPos._x = _fireLine._lastPos._x - mod._x;
		_lastPos._y = _fireLine._lastPos._y - mod._y;
		TCODLine::line(origin._x + mod._x + off._x, origin._y + mod._y + off._y, _pos->_x + mod._x, _pos->_y + mod._y, &_fireLine);
		if (std::fmodf(time, 1.0f) >= 0.5f)
			_renderer->update(*_pos, mod);
	}

	PhysicalLine _fireLine;
	PositionComponent _lastPos;
};