#include "EventManager.hpp"
#include "../include/libtcod/libtcod.hpp"
#include "../systems/CommandedSystem.hpp"
#include "../level/Level.hpp"
#include "../graphics/Gui.hpp"
#include "Geometry.hpp"
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
	float rs = static_cast<float>(1);
	int mw = 0;
	int mh = 0;
	float shot = (1 / rs * rng.getInt(0, 100) + mw) * (1 - mh / 10);
	std::cout << db::dist_sq<float>(*attacker._pos, receiver) << " " << shot << std::endl;
	if (db::dist_sq<float>(*attacker._pos, receiver) <= shot) {
		std::cout << "Shot " << receiver._x << " " << receiver._y << std::endl;
		if (attacker._inventory->_held._canDestroyWall) {
			switch (level._terrain[receiver._x][receiver._y]._renderer->_tile)
			{
			case BLOCK3:
				level._terrain[receiver._x][receiver._y] = { BLOCK2, "Damaged wall", true, false, TCODColor::lightestSepia, TCODColor::darkestSepia * 0.5f };
				break;
			case BLOCK2:
			case DOOR:
				level._terrain[receiver._x][receiver._y] = { BLOCK1, "Destroyed wall", true, true, TCODColor::lightSepia, TCODColor::darkestSepia * 0.5f };
				break;
			default:
				break;
			}
		}
		level._effect._shootEffect->_from._x = attacker._pos->_x + level._camera._pos->_x;
		level._effect._shootEffect->_from._y = attacker._pos->_y + level._camera._pos->_y;
		level._effect._shootEffect->_to._x = receiver._x + level._camera._pos->_x;
		level._effect._shootEffect->_to._y = receiver._y + level._camera._pos->_y;
		level._effect._shootEffect->_launch = true;
	}
	else {
		level._effect._shootEffect->_from._x = attacker._pos->_x + level._camera._pos->_x;
		level._effect._shootEffect->_from._y = attacker._pos->_y + level._camera._pos->_y;
		level._effect._shootEffect->_to._x = receiver._x + rng.getInt(-2, 2) + level._camera._pos->_x;
		level._effect._shootEffect->_to._y = receiver._y + rng.getInt(-2, 2) + level._camera._pos->_y;
		level._effect._shootEffect->_launch = true;
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
