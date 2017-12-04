#include "LevelState.hpp"
#include "Level.hpp"
#include "../utils/InputHandler.hpp"
#include <memory>

void PlayerTurn::enter(Level & level)
{
	level.updateComputingMap(*level._player);
	level._player->update();
}

void PlayerTurn::update(Level & level)
{
	inputHandler.onObject(*level._player);
	level._player->command();
}

void PlayerTurn::exit(Level & level)
{
}

void OtherTurn::enter(Level & level)
{
	for (auto i : level._actors) {
		level.updateComputingMap(*i);
		i->update();
	}
}

void OtherTurn::update(Level & level)
{
	for (auto i : level._actors)
		i->command();
}

void OtherTurn::exit(Level & level)
{
}

void CursorModeL::enter(Level & level)
{
}

void CursorModeL::update(Level & level)
{
	inputHandler.onObject(level._lookingCursor);
	level._lookingCursor.update(*level._player);
	//rendering
	level._lookingCursor._renderer->_bg = level._terrain[level._lookingCursor._pos->_x][level._lookingCursor._pos->_y]._renderer->_bg;
	if (std::fmodf(time, 1.0f) >= 0.5f)
		level._lookingCursor._renderer->update(*level._lookingCursor._pos, *level._camera._pos);
}

void CursorModeL::exit(Level & level)
{
	transit<PlayerTurn>(level);
}

void CursorModeF::enter(Level & level)
{
}

void CursorModeF::update(Level & level)
{
	inputHandler.onObject(level._fireCursor);
	level._fireCursor.update(*level._player);
	level._fireCursor.render(*level._player->_pos, *level._camera._pos);

}

void CursorModeF::exit(Level & level)
{
	transit<PlayerTurn>(level);
}