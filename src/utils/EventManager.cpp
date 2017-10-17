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
	if (level.terrain_[object.pos_->x_ + event._x][object.pos_->y_ + event._y].isWalkable_) {
		level.terrain_[object.pos_->x_][object.pos_->y_].actor_ = nullptr;
		object.pos_->x_ += event._x;
		object.pos_->y_ += event._y;
	}
}
