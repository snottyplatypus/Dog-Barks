#include "LevelRenderState.hpp"
#include "Level.hpp"
#include "../components/ai/AiState.hpp"
#include <iostream>

void RenderBase::enter(Level & level)
{
}

void RenderBase::update(Level & level)
{
	if (!level._player->_body->_dead)
		level.renderFov(*level._player);
	else {
		level.renderAll();
		TCODConsole::root->printEx(config.screenWidth / 2, config.screenHeight -2, TCODConsole::root->getBackgroundFlag(), TCOD_CENTER, "You are deceased.");
	}
	for (auto i : level._actors)
		if (i->_ai->_state->_id == "Surprised")
			if (std::fmodf(time, 0.6f) >= 0.3f)
				TCODConsole::root->setChar(i->_pos->_x + level._camera._pos->_x, i->_pos->_y + level._camera._pos->_y, '!');
	level._effect.update();
	gui.update();
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
	if (std::fmodf(time, 0.6f) >= 0.3f)
		level._lookingCursor._renderer->update(*level._lookingCursor._pos, *level._camera._pos);
}

void RenderCursorModeL::exit(Level & level)
{
	transit<RenderBase>(level);
	gui._state->exit(gui);
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
	gui._state->exit(gui);
}