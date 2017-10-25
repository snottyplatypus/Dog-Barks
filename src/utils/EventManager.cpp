#include "EventManager.hpp"
#include "../systems/CommandedSystem.hpp"
#include "../level/Level.hpp"
#include <iostream>

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::onNotify(Event event)
{
	switch (event) {
	case TRIGGER_LOOKING_CURSOR:
		if (level._gameState == PLAYER_TURN) {
			level._gameState = CURSOR_MODE_L;
			level._lookingCursor._pos->_x = level._player->_pos->_x;
			level._lookingCursor._pos->_y = level._player->_pos->_y;
		}
		else if (level._gameState == CURSOR_MODE_L)
			level._gameState = PLAYER_TURN;
		break;
	}
}

void EventManager::onNotify(MoveEvent event, GameObjectSystem& object)
{
	if (object._id != "cursor") {
		if (level._terrain[object._pos->_x + event._x][object._pos->_y + event._y]._isWalkable) {
			level._terrain[object._pos->_x][object._pos->_y]._actor = nullptr;
			object._pos->_x += event._x;
			object._pos->_y += event._y;
		}
	}
	else {
		if (!level._terrain[object._pos->_x + event._x][object._pos->_y + event._y]._void) {
			object._pos->_x += event._x;
			object._pos->_y += event._y;
		}
	}
}
