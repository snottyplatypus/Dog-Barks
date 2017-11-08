#include "EventManager.hpp"
#include "../include/libtcod/libtcod.hpp"
#include "../systems/CommandedSystem.hpp"
#include "../level/Level.hpp"
#include "../utils/Util.hpp"
#include "../ui/Gui.hpp"
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
	case END_TURN:
		if (level._gameState == PLAYER_TURN) {
			if (object._id == "player") {
				object._updated = false;
				level._gameState = OTHERS_UPDATE;
			}
		}
		else if (level._gameState == OTHERS_TURN) {
			[&]() { for (auto i : level._actors) { if (!i->_updated) { std::cout << "n"; } std::cout << "y"; } };
			level._gameState = PLAYER_UPDATE;
		}
		break;
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
		switch (level._gameState) {
		case CURSOR_MODE_L:
		case CURSOR_MODE_F:
			level._gameState = PLAYER_TURN;
			break;
		}
	}

}

void EventManager::onAttack(CommandedSystem& attacker, PositionComponent& receiver)
{
	float roundShot = static_cast<float>(1);
	int modWeapon = 0;
	int modHealth = 0;
	float shot = (1 / roundShot * rng.getInt(0, 100) + modWeapon) * (1 - modHealth / 10);
	if (db::dist_sq<float>(*attacker._pos, receiver) <= shot) {
		if (attacker._inventory->_held._canDestroyWall) {
			switch (db::str2int(level._terrain[receiver._x][receiver._y]._renderer->_tile.c_str()))
			{
			case db::str2int("block3"):
				level._terrain[receiver._x][receiver._y] = { "block2", "Damaged wall", true, false, level._terrain[receiver._x][receiver._y]._renderer->_fg, level._terrain[receiver._x][receiver._y]._renderer->_bg };
				break;
			case db::str2int("block2"):
			case db::str2int("door"):
				level._terrain[receiver._x][receiver._y] = { "block3", "Destroyed wall", true, true, level._terrain[receiver._x][receiver._y]._renderer->_fg, level._terrain[receiver._x][receiver._y]._renderer->_bg };
				break;
			default:
				break;
			}
		}
		if (level._terrain[receiver._x][receiver._y]._actor != nullptr) {
			auto temp = level._terrain[receiver._x][receiver._y]._actor->_body;
			temp->handleDamage(attacker._inventory->_held, (*temp)["chest"], 1);
			level._effect._bloodEffect->create(receiver, db::vec_2p(*attacker._pos, receiver), *level._camera._pos, (attacker._inventory->_held._projectiles / 2 + 1) * 1);
		}
		level._effect._shootEffect->create(*attacker._pos, receiver, *level._camera._pos);
	}
	else {
		level._effect._shootEffect->create(*attacker._pos, receiver, *level._camera._pos, PositionComponent{ rng.getInt(-2, 2), rng.getInt(-2, 2) });
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
			if (level._terrain[object._pos->_x + event._x][object._pos->_y + event._y]._actor != nullptr) {
				level._terrain[object._pos->_x + event._x][object._pos->_y + event._y]._actor->_pos->_x -= event._x;
				level._terrain[object._pos->_x + event._x][object._pos->_y + event._y]._actor->_pos->_y -= event._y;
				level._terrain[object._pos->_x + event._x][object._pos->_y + event._y]._actor = nullptr;
			}
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

void EventManager::onDeath(CommandedSystem& system)
{
	if (system._body->_dead) {
		system._renderer->_fg = TCODColor::darkRed;
		if (system._renderer->_name.find(" - dead") == std::string::npos)
			system._renderer->_name += " - dead";
		if (system._renderer->_name.find("_dead") == std::string::npos)
			system._renderer->_tile += "_dead";
	}
}
