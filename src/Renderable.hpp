#pragma once
#include "include/rltk.hpp"

struct Renderable {
	Renderable(const char tile = ' ', const rltk::color_t foreground = rltk::colors::WHITE) : tile_(tile), fg_(foreground) {}
	~Renderable() {}

	char tile_;
	rltk::color_t fg_;
	rltk::color_t bg = rltk::colors::BLACK;
};