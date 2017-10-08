#pragma once
#include "../include/rltk.hpp"
#include "../utils/gui.hpp"
#include "PositionComponent.hpp"

struct RenderComponent {
	RenderComponent(std::shared_ptr<PositionComponent> pos, const char tile = '@', const rltk::color_t foreground = rltk::colors::WHITE);
	~RenderComponent();

	void update();

	char tile_;
	rltk::color_t fg_;
	rltk::color_t bg_ = rltk::colors::BLACK;
	std::shared_ptr<PositionComponent> pos_;
};