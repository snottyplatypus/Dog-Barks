#include "LevelTurnState.hpp"
#include "Level.hpp"
#include "../utils/InputHandler.hpp"
#include "../ui/Gui.hpp"
#include "../ui/GuiState.hpp"
#include <memory>

void PlayerTurn::enter(Level & level)
{
	for (auto i : level._actors) {
		level._terrain[i->_pos->_x][i->_pos->_y]._actor = i;
		i->_renderer->_bg = level._terrain[i->_pos->_x][i->_pos->_y]._renderer->_bg;
	}
	level.updateComputingMap(*level._player);
	level._player->update();
	if (level._terrain[level._player->_pos->_x][level._player->_pos->_y]._isEscape)
		gui._state->transit<Escape>(gui);
	else if (gui._state->_id == "Escape")
		gui._state->exit(gui);
	level.timeToAssault--;
}

void PlayerTurn::update(Level & level)
{
	inputHandler.onObject(*level._player);
	inputHandler.onMenu(gui);
	level._player->command();
}

void PlayerTurn::exit(Level & level)
{
	gui._state->exit(gui);
}

void OtherTurn::enter(Level & level)
{
	for (auto i : level._actors) {
		level._terrain[i->_pos->_x][i->_pos->_y]._actor = i;
		i->_renderer->_bg = level._terrain[i->_pos->_x][i->_pos->_y]._renderer->_bg;
		if (i->_id != "player") {
			level.updateComputingMap(*i);
			i->update();
		}
	}
}

void OtherTurn::update(Level & level)
{
	for (auto i : level._actors)
		if (i->_id != "player")
			i->command();
}

void OtherTurn::exit(Level & level)
{
}

void CursorModeL::enter(Level & level)
{
	level._renderState->transit<RenderCursorModeL>(level);
}

void CursorModeL::update(Level & level)
{
	inputHandler.onObject(level._lookingCursor);
	inputHandler.onMenu(gui);
	level._lookingCursor.update(*level._player);
}

void CursorModeL::exit(Level & level)
{
	level._turnState = std::make_unique<PlayerTurn>();
	level._renderState->exit(level);
	gui._state->exit(gui);
}

void CursorModeF::enter(Level & level)
{
	level._renderState->transit<RenderCursorModeF>(level);
}

void CursorModeF::update(Level & level)
{
	inputHandler.onObject(level._fireCursor);
	inputHandler.onMenu(gui);
	level._fireCursor.update(*level._player);
}

void CursorModeF::exit(Level & level)
{
	level._turnState = std::make_unique<PlayerTurn>();
	level._renderState->exit(level);
	gui._state->exit(gui);
}
