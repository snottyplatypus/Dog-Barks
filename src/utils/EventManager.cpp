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

void EventManager::onNotify(std::unique_ptr<BaseEvent> event, CommandedSystem& object)
{
	event->react(object);
}

void EventManager::onAttack(CommandedSystem& attacker, PositionComponent& receiver, std::string part, int bullet)
{
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
