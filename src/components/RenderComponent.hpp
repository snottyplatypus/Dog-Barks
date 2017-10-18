#pragma once
#include "../include/libtcod/libtcod.hpp"
#include "PositionComponent.hpp"
#include "../Tile.hpp"
#include <string>

struct RenderComponent {
	RenderComponent(const char tile = NOTHING, const std::string name = "Object", const TCODColor foreground = TCODColor::white)
		: _tile(tile), _fg(foreground), _bg(TCODColor::black), _name(name) {}
	~RenderComponent() {}

	void update(PositionComponent &pos) const
	{
		TCODConsole::root->setChar(pos._x, pos._y, _tile);
	}
	void update(int& x, int& y) const
	{
		TCODConsole::root->setChar(x, y, _tile);
	}

	char _tile;
	TCODColor _fg;
	TCODColor _bg;
	std::string _name;
};