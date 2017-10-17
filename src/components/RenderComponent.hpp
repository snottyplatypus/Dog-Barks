#pragma once
#include "../include/libtcod/libtcod.hpp"
#include "PositionComponent.hpp"
#include "../Tile.hpp"
#include <string>

struct RenderComponent {
	RenderComponent(const char tile = NOTHING, const std::string name = "Object", const TCODColor foreground = TCODColor::white)
		: tile_(tile), fg_(foreground), bg_(TCODColor::black), name_(name) {}
	~RenderComponent() {}

	void update(PositionComponent &pos) const
	{
		TCODConsole::root->setChar(pos.x_, pos.y_, tile_);
	}
	void update(int& x, int& y) const
	{
		TCODConsole::root->setChar(x, y, tile_);
	}

	char tile_;
	TCODColor fg_;
	TCODColor bg_;
	std::string name_;
};