#pragma once
#include "Event.hpp"

struct GameObjectSystem;

class EventManager
{
public:
	EventManager();
	~EventManager();

	void onNotify(Event& event);
	void onNotify(MoveEvent event, GameObjectSystem& object);
};

extern EventManager eventManager;