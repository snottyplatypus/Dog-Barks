#include "EventManager.hpp"
#include "../include/libtcod/libtcod.hpp"
#include "../systems/CommandedSystem.hpp"
#include "../level/Level.hpp"
#include "../gui/Gui.hpp"
#include <iostream>

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::onNotify(Event event, CommandedSystem& object)
{
	switch (event) {
	case TRIGGER_LOOKING_CURSOR:
		if (level._gameState == PLAYER_TURN) {
			level._gameState = CURSOR_MODE_L;
			level._lookingCursor._pos->_x = level._player->_pos->_x;
			level._lookingCursor._pos->_y = level._player->_pos->_y;
		}
		break;
	case TRIGGER_FIRE_CURSOR:
		if (level._gameState == PLAYER_TURN) {
			level._gameState = CURSOR_MODE_F;
			level._fireCursor._pos->_x = level._player->_pos->_x;
			level._fireCursor._pos->_y = level._player->_pos->_y;
		}
		else if (level._gameState == CURSOR_MODE_F) {
			onAttack(object, level._fireCursor._lastPos);
			level._gameState = PLAYER_TURN;
		}
		break;
	case CANCEL:
		if (level._gameState == CURSOR_MODE_L)
			level._gameState = PLAYER_TURN;
		if (level._gameState == CURSOR_MODE_F)
			level._gameState = PLAYER_TURN;
	}

}

void EventManager::onAttack(CommandedSystem& attacker, PositionComponent& receiver)
{
	if (attacker._inventory->_held._canDestroyWall) {
		if (level._terrain[receiver._x][receiver._y]._renderer->_tile == BLOCK3)
			level._terrain[receiver._x][receiver._y] = { BLOCK2, "Damaged wall", true, false, TCODColor::lightestSepia, TCODColor::darkestSepia * 0.5f };
		else if (level._terrain[receiver._x][receiver._y]._renderer->_tile == BLOCK2)
			level._terrain[receiver._x][receiver._y] = { BLOCK1, "Destroyed wall", true, true, TCODColor::lightSepia, TCODColor::darkestSepia * 0.5f };
	}
}

void EventManager::onLook(LookingEvent event)
{
	std::vector<std::string> looking;
	if(event._id == LOOKING_TERRAIN)
		looking.push_back(level._terrain[event._x][event._y]._renderer->_name);
	if (level._terrain[event._x][event._y]._actor != nullptr)
		looking.push_back(level._terrain[event._x][event._y]._actor->_renderer->_name);
	gui.lookingInfo(looking);
}

void EventManager::onMove(MoveEvent event, GameObjectSystem& object)
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
