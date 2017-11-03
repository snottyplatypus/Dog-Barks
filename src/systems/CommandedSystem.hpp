#pragma once
#include "GameObjectSystem.hpp"
#include "../components/InventoryComponent.hpp"
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
	}

	~CommandedSystem() {}

	void update() 
	{
		if (_move != nullptr)
			_move->execute(*this);
		if (_interaction != nullptr) {
			_interaction->execute(*this);
			_interaction = nullptr;
		}
	}

	std::shared_ptr<InventoryComponent> _inventory;
	std::shared_ptr<Command<CommandedSystem>> _interaction;
};
