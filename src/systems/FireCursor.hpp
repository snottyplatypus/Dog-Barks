#pragma once
#include "CommandedSystem.hpp"
#include "CameraSystem.hpp"
#include "../utils/Global.hpp"
#include "../utils/Tile.hpp"
#include "../utils/EventManager.hpp"

class FireLine : public TCODLineListener {
public:
	bool putPoint(int x, int y) {
		if (TCODConsole::root->getChar(x, y) == BLOCK3)
			return false;
		TCODConsole::root->putCharEx(x, y, TCODConsole::root->getChar(x, y),
									 TCODConsole::root->getCharForeground(x, y), TCODColor::darkFlame);
		return true;
	}
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

	void update()
	{
		if (_command != nullptr)
			_command->execute(*this);
		eventManager.onNotify({ LOOKING_ACTOR, _pos->_x, _pos->_y });
	}

	void render(const PositionComponent& origin, const PositionComponent& mod)
	{
		TCODLine::line(origin._x + mod._x, origin._y + mod._y, _pos->_x + mod._x, _pos->_y + mod._y, &_fireLine);
		if (std::fmodf(time, 1.0f) >= 0.5f)
			_renderer->update({ _pos->_x + mod._x, _pos->_y + mod._y });
	}

	FireLine _fireLine;
};