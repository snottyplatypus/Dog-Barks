#pragma once
#include "Event.hpp"

struct GameObjectSystem;
struct CommandedSystem;

class EventManager
{
public:
	EventManager();
	~EventManager();

	void onNotify(Event event, CommandedSystem& object);
	void onAttack(CommandedSystem& attacker, PositionComponent& receiver);
	void onLook(LookingEvent event);
	void onMove(MoveEvent event, GameObjectSystem& object);
};

extern EventManager eventManager;