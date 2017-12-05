#pragma once
#include "Event.hpp"
#include <string>
#include <memory>

struct GameObjectSystem;
struct CommandedSystem;

class EventManager
{
public:
	EventManager();
	~EventManager();

	void onNotify(std::unique_ptr<BaseEvent> event, CommandedSystem& object);
	void onAttack(CommandedSystem& attacker, PositionComponent& receiver, std::string part, int bullet = 1);
	void onLook(LookingEvent event);
	void onMove(MoveEvent event, GameObjectSystem& object);
	void onDeath(CommandedSystem& system);
};

extern EventManager eventManager;