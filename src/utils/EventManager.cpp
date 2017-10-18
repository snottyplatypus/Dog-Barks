#include "EventManager.hpp"
#include "../systems/PlayerSystem.hpp"
#include "../level/Level.hpp"
#include <iostream>

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::onNotify(Event& event)
{
}

void EventManager::onNotify(MoveEvent event, GameObjectSystem& object)
{
	if (level._terrain[object._pos->_x + event._x][object._pos->_y + event._y]._isWalkable) {
		level._terrain[object._pos->_x][object._pos->_y]._actor = nullptr;
		object._pos->_x += event._x;
		object._pos->_y += event._y;
	}
}
