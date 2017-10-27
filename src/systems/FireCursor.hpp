#pragma once
#include "CommandedSystem.hpp"
#include "CameraSystem.hpp"
#include "../utils/Global.hpp"
#include "../utils/Tile.hpp"
#include "../utils/EventManager.hpp"
#include <iostream>

class FireLine : public TCODLineListener {
public:
	bool putPoint(int x, int y) {
		_lastPos = { x, y };
		if (TCODConsole::root->getChar(x, y) == BLOCK3)
			return false;
		TCODConsole::root->putCharEx(x, y, TCODConsole::root->getChar(x, y),
									 TCODConsole::root->getCharForeground(x, y), TCODColor::darkFlame);
		return true;
	}

	PositionComponent _lastPos;
};

struct FireCursor : public CommandedSystem
{
	FireCursor(int x = 1, int y = 1)
	{
		_renderer->_tile = CURSOR;
		_id = "cursor";
		_renderer->_bg = TCODColor::darkFlame;
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
		eventManager.onLook({ LOOKING_ACTOR, _pos->_x, _pos->_y });
	}

	void render(PositionComponent& origin, PositionComponent& mod)
	{
		_lastPos._x = _fireLine._lastPos._x - mod._x;
		_lastPos._y = _fireLine._lastPos._y - mod._y;
		TCODLine::line(origin._x + mod._x, origin._y + mod._y, _pos->_x + mod._x, _pos->_y + mod._y, &_fireLine);
		if (std::fmodf(time, 1.0f) >= 0.5f)
			_renderer->update(*_pos, mod);
	}

	FireLine _fireLine;
	PositionComponent _lastPos;
};