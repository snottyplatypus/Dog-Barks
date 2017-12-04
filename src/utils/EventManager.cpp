#include "EventManager.hpp"
#include <libtcod/libtcod.hpp>
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
		break;
	case TRIGGER_LOOKING_CURSOR:
		level._turnState->transit<CursorModeL>(level);
		level._lookingCursor._pos->_x = level._player->_pos->_x;
		level._lookingCursor._pos->_y = level._player->_pos->_y;
		gui._state = START_MENU;
		break;
	case TRIGGER_FIRE_CURSOR:
		level._turnState->transit<CursorModeF>(level);
		level._fireCursor._pos->_x = level._player->_pos->_x;
		level._fireCursor._pos->_y = level._player->_pos->_y;
		gui._state = START_MENU;
		break;
	case TRIGGER_ENTER:
		if (level._turnState->_id == "CursorModeF") {
			std::cout << object._id;
			onAttack(object, level._fireCursor._lastPos, gui._attackSelect._bodyPart, gui._attackSelect._bullets);
			level._turnState->exit(level);
			gui._state = NOTHING_SPECIAL;
		}
		break;
	case CANCEL:
		level._turnState->exit(level);
		break;
	}
}

void EventManager::onAttack(CommandedSystem& attacker, PositionComponent& receiver, std::string part, int bullet)
{
	std::cout << attacker._pos->_x << " " << attacker._pos->_y << std::endl;
	std::cout << receiver._x << " " << receiver._y << std::endl;
	int modWeapon = 0;
	int modHealth = 0;
	float shot = (1 / static_cast<float>(bullet) * rng.getInt(0, 100) + modWeapon) * (1 - modHealth / 10);
	if (db::dist_sq<float>(*attacker._pos, receiver) <= shot) {
		if (attacker._inventory->_held._canDestroyWall) {
			switch (db::str2int(level._terrain[receiver._x][receiver._y]._renderer->_tile.c_str()))
			{
			case db::str2int("block3"):
				level._terrain[receiver._x][receiver._y] = { "block2", "damaged wall", true, false, level._terrain[receiver._x][receiver._y]._renderer->_fg, level._terrain[receiver._x][receiver._y]._renderer->_bg };
				break;
			case db::str2int("block2"):
			case db::str2int("door"):
				level._terrain[receiver._x][receiver._y] = { "block1", "destroyed terrain", true, true, level._terrain[receiver._x][receiver._y]._renderer->_fg, level._terrain[receiver._x][receiver._y]._renderer->_bg };
				break;
			default:
				break;
			}
		}
		if (level._terrain[receiver._x][receiver._y]._actor != nullptr) {
			auto temp = level._terrain[receiver._x][receiver._y]._actor->_body;
			temp->handleDamage(attacker._inventory->_held, (*temp)[part], bullet);
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
	auto object = level._terrain[event._x][event._y]._actor;
	auto origin = level._terrain[event._from._x][event._from._y]._actor;
	if (origin->_computing->_map->isInFov(event._x, event._y)) {
		if (event._id == LOOKING_TERRAIN)
			gui.lookingInfo({ event._x, event._y });

		if (event._id == AIMING) {
			if (object != nullptr) {
				gui.attackMenu(*origin, *object);
			}
		}
	}
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
			gui._state = START_MENU;
		}
	}
}

void EventManager::onDeath(CommandedSystem& system)
{
	if (system._body->_dead) {
		system._renderer->_fg = TCODColor::darkRed;
		if (system._renderer->_name.find(" - dead") == std::string::npos)
			system._renderer->_name += " - dead";
		if (system._renderer->_tile.find("_dead") == std::string::npos)
			system._renderer->_tile += "_dead";
	}
}
