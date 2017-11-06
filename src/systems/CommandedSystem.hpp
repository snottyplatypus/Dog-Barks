#pragma once
#include "GameObjectSystem.hpp"
#include "../utils/EventManager.hpp"
#include "../components/InventoryComponent.hpp"
#include "../components/LivingComponent.hpp"
#include <iostream>
#include "../utils/DataManager.hpp"

struct CommandedSystem : public GameObjectSystem
{
	CommandedSystem(int x = 1, int y = 1, int tile = ACTOR, std::string name = "Actor")
	{
		_pos->_x = x;
		_pos->_y = y;
		_renderer->_tile = tile;
		_renderer->_name = name;
		_id = "actor";
		_inventory = std::make_shared<InventoryComponent>();
		_inventory->_held = dataManager._weapons["Shotgun"];
		_body = std::make_shared<LivingComponent>(dataManager._species["human"]);
		_body->init();
	}

	~CommandedSystem() {}

	void update() 
	{
		_body->update();
		if (_move != nullptr)
			_move->execute(*this);
		if (_interaction != nullptr) {
			_interaction->execute(*this);
			_interaction = nullptr;
		}
		if (_body->_dead)
			eventManager.onDeath(*this);
	}

	std::shared_ptr<InventoryComponent> _inventory;
	std::shared_ptr<LivingComponent> _body;
	std::shared_ptr<Command<CommandedSystem>> _interaction;
};
