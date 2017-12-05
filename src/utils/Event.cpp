#include "Event.hpp"
#include "EventManager.hpp"
#include "../level/Level.hpp"
#include "../ui/Gui.hpp"
#include <iostream>

void EndTurn::react(CommandedSystem & object)
{
	if (level._turnState->_id == "PlayerTurn") { //TEMP UNTIL INTERACTION/MOVEMENT COST
		if (object._id == "player") {
			object._updated = false;
			level._turnState->transit<OtherTurn>(level);
		}
	}
	else if (level._turnState->_id == "OtherTurn") { //ALSO TEMP
		bool updated = true;
		for (auto i : level._actors)
			if (!i->_updated)
				updated = false;
		if (updated)
			level._turnState->transit<PlayerTurn>(level);
	}
}

void TriggerLookingMode::react(CommandedSystem & object)
{
	level._turnState->transit<CursorModeL>(level);
	level._lookingCursor._pos->_x = level._player->_pos->_x;
	level._lookingCursor._pos->_y = level._player->_pos->_y;
	gui._state = START_MENU;
}

void TriggerAimingMode::react(CommandedSystem & object)
{
	level._turnState->transit<CursorModeF>(level);
	level._fireCursor._pos->_x = level._player->_pos->_x;
	level._fireCursor._pos->_y = level._player->_pos->_y;
	gui._state = START_MENU;
}

void TriggerEnter::react(CommandedSystem & object)
{
	if (level._turnState->_id == "CursorModeF") {
		eventManager.onAttack(object, level._fireCursor._lastPos, gui._attackSelect._bodyPart, gui._attackSelect._bullets);
		level._turnState->exit(level);
		gui._state = NOTHING_SPECIAL;
	}
}

void TriggerCancel::react(CommandedSystem & object)
{
	level._turnState->exit(level);
}
