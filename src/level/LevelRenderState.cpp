#include "LevelRenderState.hpp"
#include "Level.hpp"

void RenderBase::enter(Level & level)
{
}

void RenderBase::update(Level & level)
{
	level.renderFov(*level._player);
	level._effect.update();
}

void RenderBase::exit(Level & level)
{
}

void RenderCursorModeL::enter(Level & level)
{
}

void RenderCursorModeL::update(Level & level)
{
	RenderBase::update(level);
	level._lookingCursor._renderer->_bg = level._terrain[level._lookingCursor._pos->_x][level._lookingCursor._pos->_y]._renderer->_bg;
	if (std::fmodf(time, 1.0f) >= 0.5f)
		level._lookingCursor._renderer->update(*level._lookingCursor._pos, *level._camera._pos);
}

void RenderCursorModeL::exit(Level & level)
{
	transit<RenderBase>(level);
}

void RenderCursorModeF::enter(Level & level)
{
}

void RenderCursorModeF::update(Level & level)
{
	RenderBase::update(level);
	level._fireCursor.render(*level._player->_pos, *level._camera._pos);
}

void RenderCursorModeF::exit(Level & level)
{
	transit<RenderBase>(level);
}