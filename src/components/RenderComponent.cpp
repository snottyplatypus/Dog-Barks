#include "RenderComponent.hpp"

RenderComponent::RenderComponent(std::shared_ptr<PositionComponent> pos, const char tile, const rltk::color_t foreground)
	: tile_(tile), fg_(foreground), pos_(pos)
{
}

RenderComponent::~RenderComponent() 
{
}

void RenderComponent::update()
{
	rltk::term(MAIN_LAYER)->set_char(pos_->x_, pos_->y_, rltk::vchar{ tile_, fg_, bg_ });
}
