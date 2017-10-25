#pragma once
#include <memory>
#include "../components/RenderComponent.hpp"
#include "../utils/Tile.hpp"

struct CommandedSystem;

struct Terrain {

	Terrain(int tile = NOTHING, std::string name = "Nothing", bool isTransparent = true, bool isWalkable = false,
			TCODColor fg = TCODColor::white, TCODColor bg = TCODColor::black, bool isEscape = false)
		: _isTransparent(isTransparent), _isWalkable(isWalkable), _isEscape(isEscape), _actor(nullptr)
	{
		_renderer = std::make_shared<RenderComponent>(tile, name);
		_renderer->_fg = fg;
		_renderer->_bg = bg;
		_void = false;
	}
	~Terrain() {}

	bool _void;
	bool _isTransparent;
	bool _isWalkable;
	bool _isEscape;
	std::shared_ptr<CommandedSystem> _actor;
	std::shared_ptr<RenderComponent> _renderer;
};