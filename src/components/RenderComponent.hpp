#pragma once
#include "../include/rltk/rltk.hpp"
#include "../utils/gui.hpp"
#include "PositionComponent.hpp"

struct RenderComponent {
	RenderComponent(const char tile = ' ', const rltk::color_t foreground = rltk::colors::WHITE) : tile_(tile), fg_(foreground) {}
	~RenderComponent() {}

	void update(PositionComponent &pos) 
	{
		rltk::term(MAIN_LAYER)->set_char(pos.x_, pos.y_, rltk::vchar{ tile_, fg_, bg_ });
	}
	void update(int& x, int& y)
	{
		rltk::term(MAIN_LAYER)->set_char(x, y, rltk::vchar{ tile_, fg_, bg_ });
	}

	char tile_;
	rltk::color_t fg_;
	rltk::color_t bg_ = rltk::colors::BLACK;
};